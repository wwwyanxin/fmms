<template>
    <div>
        <Topbar ref="topbar" @paginationChange="fetchData" :pagination="tablePagination" v-loading="tableLoading"></Topbar>
        <ContentTable :articles="currentArticles"
                      :taglist="contentTagInfo.taglist"
                      :maxTagLevel="maxTagLevel"
                      :topics="topics"
                      ref="contentTable"
        ></ContentTable>
        <div>
            <ScoreBox ref="scoreBox" :articleInfo="articleInfo"></ScoreBox>
            <ContentTagBox ref="contentTagBox" :contentTagInfo="contentTagInfo"
                           :articleInfo="articleInfo"></ContentTagBox>
            <LogBox ref="logBox"></LogBox>
        </div>
    </div>
</template>

<script>
    import Topbar from './module/Topbar'
    import ContentTable from './module/ContentTable'
    import ScoreBox from "./module/ScoreBox";
    import ContentTagBox from "./module/ContentTagBox";
    import LogBox from "./module/LogBox";
    import Api from '@/service/api.js'
    import {getBlacklistMap} from '../../config/blacklist'

    export default {
        name: "Contentlib",
        components: {LogBox, ContentTagBox, ScoreBox, Topbar, ContentTable},
        data() {
            return {
                articleInfo: {
                    id: '',
                    articleid: '',
                    topicid: '',
                    createtime: '',
                    url: '',
                    subject: '',
                    summary: '',
                    logo: '',
                    flag: '',
                    wxcates: '',
                    wxtags: '',
                    xmcates: '',
                    xmvec: '',
                    xmauthor: '',
                    xmscore: '',
                    readuincount: '',
                    thumbsupuincount: '',
                    favoriteduincount: '',
                    publishtime: '',
                },
                contentTagInfo: {  // 内容打标box和table
                    taglist: {
                        taglist1: [],
                        taglist2: []
                    },
                    selected: {
                        tagSelect1: [],
                        tagSelect2: [],
                    }
                },
                topics: [   // 公众号id
                    {
                        id: '',
                        createtime: '',
                        name: '',
                        sourceid: '',
                        sourcename: '',
                        sourcetype: '',
                        flag: '',
                        introduction: '',
                        recommendlogos: {}
                    },
                ],
                tablePagination: {  //分页
                    pageIndex: 1,
                    pageSize: 50,
                    total: 0
                },
                allArticles: [],  // 黑名单过滤后的文章
                tmpArticles: [],  //用于筛选过滤
                currentArticles: [], // 用于分页
                maxTagLevel: 2,
                tableLoading: true,
                bookdate: ''
            }
        },
        created() {
            // 拉取tag信息
            this.pullTagList()
            // 拉取公众号信息
            this.pullTopics()

            this.$bus.$on('contentHandler', this.contentHandler)
        },
        beforeDestroy() {
            this.$bus.$off('contentHandler', this.contentHandler)
        },
        methods: {
            async contentHandler(param) {
                switch (param.func) {
                    // 弹出打分框
                    case 'optScore': {
                        this.articleInfo = {
                            ...param.args,
                        }
                        this.$refs.scoreBox.show()
                        break;
                    }
                    // 弹出打标签box
                    case 'optContentTag': {
                        this.articleInfo = {
                            ...param.args,
                        }
                        this.contentTagInfo.selected.tagSelect1 = param.args.tagSelect1
                        this.contentTagInfo.selected.tagSelect2 = param.args.tagSelect2
                        this.$refs.contentTagBox.show()
                        break
                    }
                    // 弹出日志框
                    case 'optLog': {
                        this.$refs.logBox.show()
                        break
                    }
                    // 文章下架
                    case 'optOutOf': {
                        this.$confirm('此操作将下架该文章 是否继续?', '提示', {
                            confirmButtonText: '确定',
                            cancelButtonText: '取消',
                            type: 'warning'
                        }).then(async () => {
                            try {
                                await Api.post('/oa/call', {...param.args})
                                await this.updateTmpArticles({func: 1, bookdate: this.bookdate})
                                this.fetchData(this.tablePagination.pageIndex)
                                this.$message({
                                    type: 'success',
                                    message: '下架成功!'
                                });
                            } catch (e) {
                                console.log(e)
                                this.$message({
                                    type: 'error',
                                    message: '下架失败!'
                                });
                            }
                        })
                        break
                    }
                    // 文章重新上架
                    case 'optPutway': {
                        this.$confirm('此操作将重新上架该文章 是否继续?', '提示', {
                            confirmButtonText: '确定',
                            cancelButtonText: '取消',
                            type: 'warning'
                        }).then(async () => {
                            try {
                                await Api.post('/oa/call', {...param.args})
                                await this.updateTmpArticles({func: 1, bookdate: this.bookdate})
                                this.fetchData(this.tablePagination.pageIndex)
                                this.$message({
                                    type: 'success',
                                    message: '上架成功!'
                                });
                            } catch (e) {
                                console.log(e)
                                this.$message({
                                    type: 'error',
                                    message: '上架失败!'
                                });
                            }
                        })
                        break
                    }

                    // 根据日期拉取文章
                    case 'selectDate': {
                        this.tableLoading = true
                        this.bookdate = param.date
                        try {
                            await this.updateArticles({func: 1, bookdate: param.date})
                            this.tablePagination.total = this.allArticles && this.allArticles.length
                            this.fetchData(1, this.tablePagination.pageSize)
                            this.$message({
                                type: 'success',
                                message: '文章已更新!'
                            });
                        } catch (e) {
                            this.$message({
                                type: 'error',
                                message: '文章更新失败!'
                            });
                            console.log(e)
                        }
                        break
                    }
                    // 修改文章,包括分数和标签
                    case 'sendUpdateArticle': {
                        try {
                            await Api.post('/oa/call', {...param.args})
                            await this.updateTmpArticles({func: 1, bookdate: this.bookdate})
                            this.fetchData(this.tablePagination.pageIndex)
                            this.$message({
                                type: 'success',
                                message: '操作成功!'
                            });
                        } catch (e) {
                            this.$message({
                                type: 'error',
                                message: '操作失败!'
                            });
                        }
                        break
                    }
                    // 模糊查询文章
                    case 'search': {
                        this.tmpArticles = this.searchArticles(param.searchValue)
                        this.tablePagination.total = this.tmpArticles.length
                        this.fetchData(1)
                        break
                    }
                    // 条件筛选文章
                    case 'filterContent': {
                        if (param.filterSelect) {
                            this.tmpArticles = this.filterSelectArticles(param.filterSelect);
                        } else {
                            this.tmpArticles = this.allArticles
                        }
                        this.tablePagination.total = this.tmpArticles.length;
                        this.fetchData(1)
                        break
                    }
                    // 找出客户端预览Previewlib选中的文章
                    case 'findPreview': {
                        this.tableLoading = true
                        // 切换活跃页面
                        this.$emit('switchActive','contentLib')
                        try {
                            // 设置topbar的值
                            this.$refs.topbar.setTime(param.args.time)
                            // 拉取文章
                            await this.updateArticles({func: 1, bookdate: this.$refs.topbar.dateFormat(param.args.time)})
                            // 搜索文章
                            this.tmpArticles = this.findArticlesById(param.args.topicId,param.args.articleId);
                            this.tablePagination.total = 1
                            this.fetchData(1, this.tablePagination.pageSize)
                            this.$message({
                                type: 'success',
                                message: 'Success!'
                            });
                        } catch (e) {
                            this.$message({
                                type: 'error',
                                message: '文章获取失败!'
                            });
                            console.log(e)
                        }
                        break
                    }
                    default: {
                        this.$message({
                            message: `${param.func} 操作有误`,
                            type: 'error'
                        })
                    }
                }
            },
            // 根据topicId articleId找到文章
            findArticlesById(topicId,articleId){
                let res = this.allArticles.find(item=>{
                    return item.articleid === articleId && item.topicid === topicId
                })
                return [res]
            },
            // 先重新请求文章,然后更新tmp,用来搜索过滤
            async updateTmpArticles(param) {
                await this.pullArticles(param)

                let tmpSet = new Set()
                for (let article of this.tmpArticles) {
                    tmpSet.add(article.id)
                }
                const result = this.allArticles.filter(article => {
                    if (tmpSet.has(article.id)) {
                        return true
                    }
                    return false;
                });

                this.tmpArticles = result
            },
            // 重新请求文章,同时将tmp赋值为allArticles,用于切换日期时更新所有文章
            async updateArticles(param) {
                try {
                    await this.pullArticles(param)
                } catch (e) {
                    throw e
                } finally {
                    this.tableLoading = false
                    this.tmpArticles = this.allArticles
                }
            },
            //拉取文章
            async pullArticles(param) {
                const res = await Api.get('/oa/call', {...param})
                // 黑名单过滤
                this.allArticles = res ? this.filterBlacklistByMap(res.articles,getBlacklistMap(this.topics),'topicid') : []

                let timer = setTimeout(() => {
                    this.tableLoading = false
                    clearTimeout(timer)
                }, 100);
            },
            // 黑名单过滤
            filterBlacklistByMap(articles,blackMap,key) {
                const res = articles.filter(article => {
                    return !blackMap.has(article[key])
                });
                return res
            },
            // 分页数据拉取
            fetchData(index) {
                this.tablePagination.pageIndex = index
                // 组件的index从1开始, 所以减一变为从0开始
                index--
                this.currentArticles = this.tmpArticles.slice(index * this.tablePagination.pageSize, (index + 1) * this.tablePagination.pageSize)
            },
            // 搜索过滤
            searchArticles(value) {
                const searchItem = ['subject', 'summary']
                const res = this.allArticles.filter(article => {
                    for (let item of searchItem) {
                        if (article[item].indexOf(value) > -1) {
                            return true
                        }
                    }
                    return false
                });
                return res
            },
            // 文章筛选过滤
            filterSelectArticles(filterSelect) {
                const res = this.allArticles.filter(article => {
                    let statusRight = false
                    let scoreRight = false
                    // 未选择筛选时,全部通过
                    if(filterSelect.statusArr && filterSelect.statusArr.length === 0){
                        statusRight = true
                    }
                    if (filterSelect.scoreArr && filterSelect.scoreArr.length === 0) {
                        scoreRight = true
                    }
                    for (let status of filterSelect.statusArr) {
                        if (this.$refs.contentTable.articleStatus(article) === status) {
                            statusRight = true
                            break
                        }
                    }
                    for(let score of filterSelect.scoreArr){
                        if (article.xmscore === score) {
                            scoreRight = true
                            break
                        }
                    }
                    return statusRight && scoreRight
                });
                return res
            },
            // 拉取taglist
            pullTagList() {
                Api.get('/oa/call', {
                    func: 11,
                    gettaginforeq: JSON.stringify({
                        level: 1
                    })
                }).then((res) => {
                    this.contentTagInfo.taglist.taglist1 = this.fidFilter(res.taglist, 0)
                })
                Api.get('/oa/call', {
                    func: 11,
                    gettaginforeq: JSON.stringify({
                        level: 2
                    })
                }).then((res) => {
                    this.contentTagInfo.taglist.taglist2 = this.fidFilter(res.taglist, 0)
                })
            },
            // 筛选fid为某个值的list
            fidFilter(taglist, fid) {
                let res = taglist.filter(item => {
                    return item.fid === fid
                })
                return res || []
            },
            // 拉取公众号信息
            async pullTopics() {
                const res = await Api.get('/oa/call', {
                    func: 14
                })
                this.topics = res.topics || []
            }
        }
    }
</script>

<style scoped>

</style>
