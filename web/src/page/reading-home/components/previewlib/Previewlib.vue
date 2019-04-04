<template>
    <div>
        <Topbar @changeDate="pullPreview"></Topbar>
        <PreviewTable :previewInfo="previewInfo"
                      v-loading="tableLoading"
        ></PreviewTable>
    </div>
</template>

<script>
    import PreviewTable from './module/PreviewTable'
    import Api from '@/service/api.js'
    import Topbar from "../previewlib/module/Topbar";

    export default {
        name: "Previewlib",
        components: {Topbar, PreviewTable},
        data() {
            return {
                previewInfo: {
                    bannerarticle: {
                        id: '',
                        createtime: '',
                        topicid: '',
                        url: '',
                        subject: '',
                        summary: '',
                        logo: '',
                        flag: '',
                        wxcates: '',
                        xmtags: {},
                        xmauthor: '',
                        xmscore: '',
                        readuincount: '',
                        thumbsupuincount: '',
                        favoriteduincount: '',
                        publishtime: '',
                        tagtime: '',
                        docid: '',
                    },
                    recommendarticles: [
                        {
                            id: '',
                            createtime: '',
                            topicid: '',
                            url: '',
                            subject: '',
                            summary: '',
                            logo: '',
                            flag: '',
                            wxcates: '',
                            xmtags: {},
                            xmauthor: '',
                            xmscore: '',
                            readuincount: '',
                            thumbsupuincount: '',
                            favoriteduincount: '',
                            publishtime: '',
                            tagtime: '',
                            docid: '',
                        }
                    ],

                    recommendtopics: [
                        {
                            id: '',
                            name: '',
                            articlenum: '',
                            tags: {},
                            flag: '',
                            sortid: '',
                            subname: '',
                            logo: '',
                        }
                    ],
                    clusterinfos: [],
                    daterecommendarticles: [],
                    recommendtime: '',
                },
                tableLoading: true,
                bookdate: ''
            }
        },
        methods: {
            // 按日期拉取客户端文章
            async pullPreview(date){
                this.tableLoading = true
                const res = await Api.get('/oa/call', {
                    func: 19,
                    getdaterecommendarticlereq: JSON.stringify({
                        datetime: date.getTime()/1000,
                        isgetlast: false,
                    })
                })
                this.previewInfo = res.data
                this.tableLoading = false
            }
        }
    }
</script>

<style scoped>

</style>
