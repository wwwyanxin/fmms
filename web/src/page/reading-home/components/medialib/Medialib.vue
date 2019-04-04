<template>
    <div>
        <MediaTable :topics="topics" :XMBookBWInfoList="XMBookBWInfoList" :XMBookBWInfoFlag="XMBookBWInfoFlag" v-loading="tableLoading"></MediaTable>
        <EditMedia ref="editMedia" :info="editInfo"></EditMedia>
    </div>
</template>

<script>

    import MediaTable from "./module/MediaTable";
    import EditMedia from "./module/EditMedia";
    import Api from '@/service/api.js'
    import {cloneDeep} from '@/lib/util'

    export default {
        name: "Medialib",
        components: {MediaTable, EditMedia},
        data() {
            return {
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
                XMBookBWInfoFlag: {								// 结果定义
                    kXMBookBWInfoFlagIsBlack: 0x01,			// 黑名单
                    kXMBookBWInfoFlagIsWhite: 0x02,			// 白名单
                },
                XMBookBWInfoCondFieldIDVT: {					// 匹配值的类型
                    kXMBookBWInfoCondFieldIDVTString: 1,			//	值的类型为字符串
                    kXMBookBWInfoCondFieldIDVTNumber: 2,			//	值的类型为数值
                },
                XMBookBWInfoCondFuncID: {						// 匹配函数定义
                    kXMBookBWInfoCondSubstr: 1,			//	子串比较
                },
                XMBookBWInfoCondFieldID: {							// 匹配字段定义
                    kXMBookBWInfoCondFieldIDSubject: 1,			//	主题字段
                },
                XMBookBWInfoList: {
                    fieldid2name: [	// 匹配字段id和名字映射
                        {
                            id: 1,					// 唯一标识
                            name: '',				// 中文名
                            vt: 3,					// 值类型 XMBookBWInfoCondFieldIDVT
                        },
                    ],
                    funcid2name: [		// 匹配方法id和名字映射
                        {
                            id: 1,					// 唯一标识
                            name: '',				// 中文名
                            vt: 3,					// 值类型 XMBookBWInfoCondFieldIDVT
                        },
                    ],
                    bwinfos: [	// 条件集合
                        {
                            bwinfo: {
                                topicid: 1, // 话题id
                                wblist: [   // 黑白条件集合
                                    {
                                        bwid: 1,	 // 唯一id
                                        flag: 2,	 // 标志位 XMBookBWInfoFlag
                                        autotags: {  // 标签集合
                                            leveldatas: [
                                                {
                                                    level: 1,             // 文章属于第level级标签
                                                    tagids: ['1', '2']    // 文章囊括的标签名
                                                }
                                            ]
                                        },
                                        condtions: [  // 匹配条件集合
                                            {
                                                fieldid: 1,						// 匹配字段名称 XMBookBWInfoCondFieldID
                                                fieldval_intmin: 2,				// 匹配数值最小
                                                fieldval_intmax: 3,				// 匹配数值最大
                                                fieldval_str: '',				// 匹配字符串
                                                funcid: 5,						// 匹配方法 XMBookBWInfoCondFuncID
                                            }
                                        ]
                                    }
                                ]
                            }
                        }
                    ]
                },
                editInfo: {
                    XMBookBWInfoFlag: {								// 结果定义
                        kXMBookBWInfoFlagIsBlack: 0x01,			// 黑名单
                        kXMBookBWInfoFlagIsWhite: 0x02,			// 白名单
                    },
                    XMBookBWInfoCondFieldIDVT: {					// 匹配值的类型
                        kXMBookBWInfoCondFieldIDVTString: 1,			//	值的类型为字符串
                        kXMBookBWInfoCondFieldIDVTNumber: 2,			//	值的类型为数值
                    },
/*                    XMBookBWInfoCondFuncID: {						// 匹配函数定义
                        kXMBookBWInfoCondSubstr: 1,			//	子串比较
                    },
                    XMBookBWInfoCondFieldID: {							// 匹配字段定义
                        kXMBookBWInfoCondFieldIDSubject: 1,			//	主题字段
                    },*/
                    topicInfo: {},
                    taglist: {
                        taglist1: [],
                        taglist2: []
                    },
                    bwinfo: {
                        topicid: '', // 话题id
                        wblist: [   // 黑白条件集合
                            {
                                bwid: '',	 // 唯一id
                                flag: '',	 // 标志位 XMBookBWInfoFlag
                                autotags: {  // 标签集合
                                    leveldatas: [
                                        {
                                            level: '',             // 文章属于第level级标签
                                            tagids: []    // 文章囊括的标签名
                                        }
                                    ]
                                },
                                condtions: [  // 匹配条件集合
                                    {
                                        fieldid: '',						// 匹配字段名称 XMBookBWInfoCondFieldID
                                        fieldval_intmin: '',				// 匹配数值最小
                                        fieldval_intmax: '',				// 匹配数值最大
                                        fieldval_str: '',				// 匹配字符串
                                        funcid: '',						// 匹配方法 XMBookBWInfoCondFuncID
                                    }
                                ]
                            }
                        ]
                    },
                    fieldid2name: [	// 匹配字段id和名字映射
                        {
                            id: '',					// 唯一标识
                            name: '',				// 中文名
                            vt: '',					// 值类型 XMBookBWInfoCondFieldIDVT   这个决定输入的字段是什么类型
                        },
                    ],
                    funcid2name: [		// 匹配方法id和名字映射
                        {
                            id: '',					// 唯一标识
                            name: '',				// 中文名
                            vt: '',					// 值类型 XMBookBWInfoCondFieldIDVT   没啥用
                        },
                    ]
                },
                tableLoading: true,
            }
        },
        created() {
            // 拉取tag信息
            this.pullTagList()
            // 拉取公众号信息
            this.pullTopics()
            // 拉取黑白名单信息
            this.pullBWInfoList()
        },
        methods: {
            // 发送修改的信息
            async sendUpdateMedia(param){
                await Api.post('/oa/call', param);
                this.pullBWInfoList();
            },
            // 拉取黑白名单信息
            async pullBWInfoList() {
                this.tableLoading = true
                const res = await Api.get('/oa/call', {
                    func: 20
                })
             /*   Api.post('/oa/call',{
                    func:21,
                    updatebwinforeq:JSON.stringify({"bwinfo":{"topicid":417,"wblist":[{"flag":1}]}})
                })*/
                this.XMBookBWInfoList = res.list || []
                this.tableLoading = false
            },
            // 拉取公众号信息
            async pullTopics() {
                this.tableLoading = true
                const res = await Api.get('/oa/call', {
                    func: 14
                })
                this.topics = res.topics || []
                this.tableLoading = false
            },
            // 弹出修改规则box
            updateEditBox(index, row) {
                this.editInfo.topicInfo = cloneDeep(this.topics[index])
                this.editInfo.fieldid2name = cloneDeep(this.XMBookBWInfoList.fieldid2name)
                this.editInfo.funcid2name = cloneDeep(this.XMBookBWInfoList.funcid2name)
                let bwinfo = this.XMBookBWInfoList.bwinfos.find(item => {
                    return item.topicid === row.id
                })
                if (!bwinfo) {
                    this.editInfo.bwinfo.topicid = row.id;
                    this.editInfo.bwinfo.wblist = [];
                } else {
                    this.editInfo.bwinfo = cloneDeep(bwinfo);
                }
                this.$refs.editMedia.show()
            },
            // 拉取taglist
            pullTagList() {
                Api.get('/oa/call', {
                    func: 11,
                    gettaginforeq: JSON.stringify({
                        level: 1
                    })
                }).then((res) => {
                    this.editInfo.taglist.taglist1 = this.fidFilter(res.taglist, 0)
                })
                Api.get('/oa/call', {
                    func: 11,
                    gettaginforeq: JSON.stringify({
                        level: 2
                    })
                }).then((res) => {
                    this.editInfo.taglist.taglist2 = this.fidFilter(res.taglist, 0)
                })
            },
            // 筛选fid为某个值的list
            fidFilter(taglist, fid) {
                let res = taglist.filter(item => {
                    return item.fid === fid
                })
                return res || []
            },
        }
    }
</script>

<style scoped>

</style>
