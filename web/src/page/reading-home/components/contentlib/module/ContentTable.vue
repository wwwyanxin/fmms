<template>
    <div>
        <el-table
                :data="articles"
                style="width: 100%"
                stripe
                :height="tableHeight"
                highlight-current-row
                @current-change="handleCurrentChange"
        >
            <el-table-column
                    prop="contentFromInfo"
                    label="内容信息"
                    width="192"
            >
                <template slot-scope="scope">
                    <el-card class="box-card">
                        <div @click='tableClickHandler(scope.row)' style="cursor:pointer">
                            序号:
                            <br>
                            <el-tag disable-transitions size="medium" type="info" hit>{{ scope.row.id }}</el-tag>
                            <br>
                            来源媒体:
                            <br>
                            <el-tag disable-transitions size="medium" type="info" hit>
                                {{topicIdHandler(scope.row).sourcename}}
                            </el-tag>
                            <br>
                            发布时间:
                            <br>
                            <el-tag disable-transitions size="medium" type="info" hit>{{
                                formatDate(scope.row.publishtime) }}
                            </el-tag>
                        </div>
                    </el-card>
                </template>
            </el-table-column>

            <el-table-column
                    prop="logo"
                    label="预览图"
                    width="200">
                <template slot-scope="scope">
                    <a :href="scope.row.logo" target="_blank">
                        <img :src="scope.row.logo" width="190">
                    </a>
                </template>
            </el-table-column>

            <el-table-column
                    prop="subject"
                    label="内容标题"
                    width="250"
                    show-overflow-tooltip>
            </el-table-column>
            <el-table-column
                    prop="summary"
                    label="摘要"
            >
                <template slot-scope="scope">
                    <p @click='tableClickHandler(scope.row)' style="cursor:pointer">{{scope.row.summary || '无摘要'}}</p>
                </template>
            </el-table-column>


            <el-table-column
                    prop="statusAndScore"
                    label="状态及评分"
                    width="120"
            >
                <template slot-scope="scope">
                    <el-tag class="statusTag" style="font-size: 16px;" hit disable-transitions
                            :type="statusType(articleStatus(scope.row))" size="medium">{{ articleStatus(scope.row) }}
                    </el-tag>
                    <el-tag class="statusTag" style="font-size: 18px;" disable-transitions type="warning">分数:{{
                        scope.row.xmscore }}
                    </el-tag>
                </template>
            </el-table-column>


            <el-table-column
                    prop="categoryTag"
                    :label="itemLevel + '级标签'"
                    width="140"
                    v-for="itemLevel in maxTagLevel"
            >
                <template slot-scope="scope">
                    <el-tag disable-transitions hit :type="itemLevel%2 ===0 ? 'success' : 'primary'"
                            v-for="(item,index) in tagidsHandler(scope.row.xmtags,itemLevel)">{{item.name}}
                    </el-tag>
                </template>
            </el-table-column>


            <el-table-column
                    prop="operation"
                    label="操作区"
                    width="180"
            >
                <template slot-scope="scope">
                    <el-button
                            style="margin:0"
                            size="mini"
                            type="warning" plain round
                            @click="handleScore(scope.$index, scope.row)">打分
                    </el-button>
                    <el-button
                            style="margin:0"
                            size="mini"
                            type="primary" plain round
                            @click="handleContentTag(scope.$index, scope.row)">内容打标
                    </el-button>
                    <el-button
                            v-if="articleStatus(scope.row) === '已下架'"
                            style="margin:0"
                            size="mini"
                            type="info" plain round
                            @click="handlePutaway(scope.$index, scope.row)">恢复上架
                    </el-button>
                    <el-button
                            v-else
                            style="margin:0"
                            size="mini"
                            type="danger" plain round
                            @click="handleOutOf(scope.$index, scope.row)">下架
                    </el-button>

                    <el-button
                            style="margin:0"
                            size="mini" plain round
                            @click="handleLog(scope.$index, scope.row)">日志
                    </el-button>
                </template>
            </el-table-column>
        </el-table>
    </div>
</template>

<script>
    import dayjs from 'dayjs'

    export default {
        name: 'ContentTable',
        props: {
            articles: {
                type: Array,
                default: undefined
            },
            topics: {
                type: Array
            },
            taglist: {},
            maxTagLevel: {},
        },
        data() {
            return {
                //multipleSelection: [],  //复选框
                currentRow: null,
                tableTop: document.documentElement.clientHeight, //table的高度
                tagMap: {        //加快tag匹配速度
                    tagMap1: {},
                    tagMap2: {}
                },
                topicMap: {},
                articleFlag: {
                    kXMBookArticleFlagIsUrl: 0x01,				// url字段是ssID
                    kXMBookArticleFlagIsNoPush: 0x04,			// 文章不需要推送
                    kXMBookArticleFlagIsCommArticle: 0x08,		// 文章是全员推送文章
                    kXMBookArticleFlagIsKeyArticle: 0x10,		// 文章是主推文章
                    kXMBookArticleFlagIsRecommend: 0x20,		// 文章是推荐文章
                    kXMBookArticleFlagIsSelected: 0x40,		// 文章已经被选了（被用了）
                    kXMBookArticleFlagIsOffShelved: 0x80,		// 文章被下架了（淘汰）
                }
            }
        },
        mounted() {
            window.onresize = () => {
                this.tableTop = document.documentElement.clientHeight
            }
            // 建立映射
            this.tagMap.tagMap1 = this.list2Map(this.taglist.taglist1)
            this.tagMap.tagMap2 = this.list2Map(this.taglist.taglist2)
            this.topicMap = this.list2Map(this.topics)
        },
        watch: {
            taglist: {
                deep: true,
                handler: function () {
                    // 建立标签信息的映射
                    this.tagMap.tagMap1 = this.list2Map(this.taglist.taglist1)
                    this.tagMap.tagMap2 = this.list2Map(this.taglist.taglist2)
                }
            },
            topics() {
                // 建立公众号信息的映射
                this.topicMap = this.list2Map(this.topics)
            },
        },
        methods: {
            // 判断文章的状态
            articleStatus(article) {
                // 判断此文章的flag的某个值是否为1
                let flagIs = (flag) => {
                    return (article.aflag & flag) === flag
                }


                     // 文章被下架
                if (flagIs(this.articleFlag.kXMBookArticleFlagIsOffShelved)) {
                    return '已下架';
                }
                else if (flagIs(this.articleFlag.kXMBookArticleFlagIsSelected)) {
                    // 文章已选中
                    return '已选中'
                } else if (flagIs(this.articleFlag.kXMBookArticleFlagIsRecommend)) {
                    // 文章是推荐文章
                    return '审核通过';
                } else {
                    return '未审核';
                }
            },
            // 根据文章的状态不同,显示不同颜色
            statusType(status) {
                switch (status) {
                    case '未审核':
                        return 'info';
                    case '审核通过':
                        return 'success';
                    case '已下架':
                        return 'danger';
                    case '已选中':
                        return 'primary';
                    default:
                        return '';
                }
            },
            // 格式化日期显示
            formatDate(time) {
                let date = dayjs(time * 1000)
                return date.format('YYYY年M月D日  h:mm ')
            },
            // 打分
            handleScore(index, row) {
                this.$bus.$emit('contentHandler', {
                    func: 'optScore',
                    args: {
                        ...row
                    }
                })
            },
            // 文章打标签
            handleContentTag(index, row) {
                let args = {...row}
                args.tagSelect1 = this.tagidsHandler(row.xmtags, 1)
                args.tagSelect2 = this.tagidsHandler(row.xmtags, 2)
                this.$bus.$emit('contentHandler', {
                    func: 'optContentTag',
                    args: args
                })
            },
            // todo 日志,后台还没接口,待补齐
            handleLog(index, row) {
                this.$bus.$emit('contentHandler', {
                    func: 'optLog'
                })
            },
            // 文章下架
            handleOutOf(index, row) {
                this.$bus.$emit('contentHandler', {
                    func: 'optOutOf',
                    args: {
                        func: 3,
                        updateArticlereq: JSON.stringify({
                            topicid: row.topicid,
                            articleid: row.articleid,
                            appendflag: this.articleFlag.kXMBookArticleFlagIsOffShelved
                        })
                    }
                })
            },
            // 恢复上架
            handlePutaway(index, row) {
                this.$bus.$emit('contentHandler', {
                    func: 'optPutway',
                    args: {
                        func: 3,
                        updateArticlereq: JSON.stringify({
                            topicid: row.topicid,
                            articleid: row.articleid,
                            removeflag: this.articleFlag.kXMBookArticleFlagIsOffShelved
                        })
                    }
                })
            },
            tableClickHandler(row) {
                window.open(row.url)
            },
            handleCurrentChange(val) {
                this.currentRow = val;
            },
            // 将指定级别的tag,从id返回完成info
            tagidsHandler(tags, itemLevel) {
                let tagIds
                if (tags && tags.leveldatas) {
                    let levelItem = tags.leveldatas.find(item => {
                        return item.level === itemLevel
                    })
                    if (levelItem && Array.isArray(levelItem.tagids)) {
                        tagIds = levelItem.tagids;
                    } else {
                        return null
                    }
                }
                let tagMap = this.tagMap['tagMap' + itemLevel]
                return this.matchMap(tagIds, tagMap) || {}
            },
            // 从topicid返回完成topic
            topicIdHandler(row) {
                const res = this.matchMap([row.topicid], this.topicMap) || ['']
                return res[0]
            },
            // 通过map查询到相匹配的List
            matchMap(keyList, map) {
                let distList = []
                if (map.size < 1 || !keyList) {
                    return []
                }
                for (let item of keyList) {
                    distList.push(map.get(item) || {})
                }
                return distList
            },
            // 建立map映射, 加快索引
            list2Map(list, key = 'id') {
                let map = new Map()
                for (let item of list) {
                    map.set(item[key], item)
                }
                return map
            },
        },
        computed: {
            tableHeight() {
                let height = (this.tableTop - 112) + 'px'
                return height
            },
        }
    }
</script>

<style scoped>
    .statusTag {
        margin-bottom: 10px;
        height: 43px;
        padding: 0 18px;
        line-height: 42px;
    }

</style>
