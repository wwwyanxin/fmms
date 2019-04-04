<template>
    <div>
        <Topbar></Topbar>
        <EditCluster ref="editClusterBox"
                     :info="concatInfo"
                     :clusterFlag="clusterFlag"
        ></EditCluster>
        <ClusterTable
                :clusterinfos="clusterinfos"
                :taglist="concatInfo.taglist"
                :clusterFlag="clusterFlag"
                v-loading="tableLoading"
        ></ClusterTable>
    </div>
</template>

<script>
    import ClusterTable from "./module/ClusterTable";
    import Topbar from "./module/Topbar";
    import EditCluster from "./module/EditCluster";
    import Api from '@/service/api.js'


    export default {
        name: "Clusterlib",
        components: {EditCluster, ClusterTable, Topbar},
        data() {
            return {
                clusterinfos: {
                    infos: [
                        {
                            id: '',     //
                            name: '',    //
                            articlenum: '',
                            flag: '',
                            sortid: '',
                            tags: {
                                leveldatas: [
                                    {
                                        level: 1,
                                        tagids: 2,
                                    }
                                ]
                            }
                        }
                    ]
                },
                concatInfo: {
                    taglist:{
                        taglist1:[],
                    },
                    selected:{
                        tagSelect1:[],
                    },
                    id: '',
                    name: '',
                    flag: '',
                    sortid: '',
                    articlenum: '',
                },
                clusterFlag: {
                    eXMBookClusterInfoFlagIsRuning: 0x01, // 运营中
                    eXMBookClusterInfoFlagIsOffTheShelved: 0x02, // 下线了
                    eXMBookClusterInfoFlagIsRecommendMon: 0x04, // 周一推荐
                    eXMBookClusterInfoFlagIsRecommendTUE: 0x08, // 周二推荐
                    eXMBookClusterInfoFlagIsRecommendWED: 0x10, // 周三推荐
                    eXMBookClusterInfoFlagIsRecommendTHU: 0x20, // 周四推荐
                    eXMBookClusterInfoFlagIsRecommendFRI: 0x40, // 周五推荐
                    eXMBookClusterInfoFlagIsSpecialCluster: 0x80, // 特殊卡片(屏蔽掉编辑)
                },
                tableLoading:true
            }
        },
        created() {
            this.updateData()
            this.$bus.$on('clusterHandler', this.clusterHandler)
        },
        beforeDestroy() {
            this.$bus.$off('clusterHandler', this.clusterHandler)
        },
        methods: {
            async clusterHandler(param) {
                switch (param.func) {
                    case 'editClusterTagBox': {
                        this.concatInfo.id = param.args.id
                        this.concatInfo.name = param.args.name
                        this.concatInfo.flag = param.args.flag
                        this.concatInfo.sortid = param.args.sortid
                        this.concatInfo.articlenum = param.args.articlenum
                        this.concatInfo.selected.tagSelect1 = param.args.tagSelect1
                        this.$refs.editClusterBox.show()
                        break;
                    }
                    case 'sendUpdateCluster':{
                        if (this.checkName(JSON.parse(param.args.updateclusterinforeq).clusterinfo)) {
                            await Api.post('/oa/call', {...param.args});
                            this.updateData();
                        }
                        break;
                    }
                    case 'sendAddCluster':{
                        if (this.checkName(JSON.parse(param.args.addclusterinforeq).clusterinfo)) {
                            await Api.post('/oa/call', {...param.args})
                            this.updateData()
                        }
                        break
                    }
                }
            },
            async updateData() {
                this.pullTagList()
                const res = await Api.get('/oa/call', {
                    func: 7,
                    getclusterinforeq: JSON.stringify({
                        /*level: 1*/
                    })
                })

                this.clusterinfos = res.clusterinfos
            },
            // 拉取taglist
            pullTagList() {
                let _this=this
                Api.get('/oa/call', {
                    func: 11,
                    gettaginforeq: JSON.stringify({
                        level: 1
                    })
                }).then((res) => {
                    _this.concatInfo.taglist.taglist1 = this.fidFilter(res.taglist,0)
                })
                let timer = setTimeout(() => {
                    this.tableLoading = false
                    clearTimeout(timer)
                }, 300);
            },
            // 筛选fid为某个值的taglist
            fidFilter(taglist, fid) {
                let res = taglist.filter(item=>{
                    return item.fid === fid
                })
                return res || []
            },
            checkName(param) {
                const has = this.clusterinfos.infos.some(item=>{
                    if (item.name === param.name) {
                        if (item.id) {
                            return item.id !== param.id;
                        } else {
                            return true
                        }
                    }
                })
                if (has) {
                    this.$message({
                        type: 'error',
                        message: `卡片: ${param.name} 已存在!`
                    })
                }
                return !has
            }
        }
    }
</script>

<style scoped>

</style>
