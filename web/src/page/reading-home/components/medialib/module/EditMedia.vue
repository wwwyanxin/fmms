<template>
    <el-dialog :title="info.topicInfo.sourcename" :visible.sync="dialogVisible" width="800px" top="5vh">
        <el-form style="max-height: 600px;overflow-y: auto;">
            <el-form-item label="筛选方式:">
                <el-radio-group v-model="form.mode">
                    <el-radio-button class="logic-radio" label="none">无</el-radio-button>
                    <el-radio-button class="logic-radio" label="outOf">全部下架</el-radio-button>
                    <el-radio-button class="logic-radio" label="bindTag">全部通过并关联</el-radio-button>
                    <el-radio-button class="logic-radio" style="display: inline-block;" label="custom">自定义规则
                    </el-radio-button>
                </el-radio-group>
            </el-form-item>
            <div v-show="form.mode === 'bindTag'">
                <SearchAppend :info="form.searchTagForBindTag.searchTag1"
                              style="margin: 50px 0px 0px 100px;"></SearchAppend>
                <SearchAppend :info="form.searchTagForBindTag.searchTag2"
                              style="margin: 50px 0px 0px 100px;"></SearchAppend>
            </div>
            <div v-show="form.mode === 'custom'">
                <el-button type="success" size="mini" @click="addRule" style="margin-left:10px;">添加规则</el-button>
                <el-card v-for="(wbItem,wbIndex) in form.wblist" class="box-card" v-show="form.mode === 'custom'"
                         style="margin:10px;">
                    <el-form-item :label="`规则:${wbIndex + 1}`">
                        <div style="display:inline-block;text-align:right;width: 610px;;">
                            <el-button @click="removeRule(wbIndex)" type="danger" size="mini" style="float:right">删除规则
                            </el-button>
                        </div>
                        <div v-for="(conditionItem,conditionIndex) in wbItem.condtions"
                             style="min-height: 45px;margin:10px;">
                            <el-card class="condition-card" :body-style="{padding:'5px'}"
                                     style="display: inline-block;">
                                条件{{conditionIndex + 1}}:
                                <el-select v-model="conditionItem.fieldid" placeholder="选择字段" size="mini"
                                           style="width:100px;">
                                    <el-option
                                            v-for="fieldItem in info.fieldid2name"
                                            :label="fieldItem.name"
                                            :value="fieldItem.id">
                                    </el-option>
                                </el-select>
                                ,
                                <el-select v-model="conditionItem.funcid" placeholder="选择功能" size="mini"
                                           style="width:100px;">
                                    <el-option
                                            v-for="funcItem in info.funcid2name"
                                            :label="funcItem.name"
                                            :value="funcItem.id">
                                    </el-option>
                                </el-select>
                                <el-input
                                        v-if="fieldById(conditionItem.fieldid).vt === info.XMBookBWInfoCondFieldIDVT.kXMBookBWInfoCondFieldIDVTString"
                                        placeholder="请输入内容"
                                        v-model="conditionItem.fieldval_str"
                                        type="textarea"
                                        autosize
                                        size="mini"
                                        style="width:200px;vertical-align: top;padding-top: 6px;"
                                >
                                </el-input>
                                <span v-else-if="fieldById(conditionItem.fieldid).vt === info.XMBookBWInfoCondFieldIDVT.kXMBookBWInfoCondFieldIDVTNumber">
                                    <el-input
                                            type="number"
                                            placeholder="最小值"
                                            v-model="conditionItem.fieldval_intmin"
                                            size="mini"
                                            style="width:89px;"
                                    ></el-input>
                                    —
                                    <el-input
                                            type="number"
                                            placeholder="最大值"
                                            v-model="conditionItem.fieldval_intmax"
                                            size="mini"
                                            style="width:89px;"
                                    ></el-input>
                                </span>
                                的文章
                            </el-card>
                            <i @click="removeCondition(wbIndex,conditionIndex)" class="el-icon-remove"
                               style="margin: 13px 0px 0px 10px;font-size: 25px;vertical-align: top;cursor: pointer"></i>
                        </div>
                    </el-form-item>
                    <i @click="addCondition(wbItem)"
                       class="el-icon-circle-plus"
                       style="margin: -30px 37px 17px 17px;font-size: 30px;vertical-align: top;cursor: pointer;"></i>
                    <el-form-item label="执行操作:">
                        <el-radio-group v-model="wbItem.flag">
                            <el-radio border class="logic-radio"
                                      :label="info.XMBookBWInfoFlag.kXMBookBWInfoFlagIsBlack">下架
                            </el-radio>
                            <el-radio border class="logic-radio"
                                      :label="info.XMBookBWInfoFlag.kXMBookBWInfoFlagIsWhite">通过并关联
                            </el-radio>
                        </el-radio-group>
                        <div v-show="wbItem.flag === info.XMBookBWInfoFlag.kXMBookBWInfoFlagIsWhite">
                            <SearchAppend :info="wbItem.searchTagForCustom.searchTag1"
                                          style="margin: 30px;"></SearchAppend>
                            <SearchAppend :info="wbItem.searchTagForCustom.searchTag2"
                                          style="margin: 30px;"></SearchAppend>
                        </div>
                    </el-form-item>
                </el-card>
            </div>
        </el-form>
        <div slot="footer" class="dialog-footer">
            <el-button @click="dialogVisible = false">取 消</el-button>
            <el-button type="primary" @click="confirm">确 定</el-button>
        </div>
    </el-dialog>
</template>

<script>
    import SearchAppend from "@/components-ui/searchAppend/SearchAppend";
    import {cloneDeep} from '@/lib/util'

    export default {
        name: "EditMedia",
        components: {SearchAppend},
        props: {
            info: {
                XMBookBWInfoFlag: {								// 结果定义
                    kXMBookBWInfoFlagIsBlack: 0x01,			// 黑名单
                    kXMBookBWInfoFlagIsWhite: 0x02,			// 白名单
                },
                XMBookBWInfoCondFieldIDVT: {					// 匹配值的类型
                    kXMBookBWInfoCondFieldIDVTString: 1,			//	值的类型为字符串
                    kXMBookBWInfoCondFieldIDVTNumber: 2,			//	值的类型为数值
                },
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
                        vt: '',					// 值类型 XMBookBWInfoCondFieldIDVT
                    },
                ],
                funcid2name: [		// 匹配方法id和名字映射
                    {
                        id: '',					// 唯一标识
                        name: '',				// 中文名
                        vt: '',					// 值类型 XMBookBWInfoCondFieldIDVT
                    },
                ]
            },
        },
        data() {
            return {
                dialogVisible: false,
                form: {
                    mode: 'none',
                    searchTagForBindTag: {  //当为bindTag模式时,所用的标签
                        searchTag1: {},
                        searchTag2: {},
                    },
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
                            ],
                            searchTagForCustom: {  //当为custom模式时,所用的标签
                                searchTag1: {},
                                searchTag2: {},
                            },
                        }
                    ]

                },

                tagMap: {        //加快tag匹配速度
                    tagMap1: {},
                    tagMap2: {}
                },
            }
        },
        watch: {
            'info.bwinfo.topicid'() {
                this.tagMap.tagMap1 = this.list2Map(this.info.taglist.taglist1)
                this.tagMap.tagMap2 = this.list2Map(this.info.taglist.taglist2)
                this.updateInfo()
            }
        },
        methods: {
            fieldById(fileId) {
                return this.info.fieldid2name.find(item => item.id === fileId) || {}
            },
            funcById(funcId) {
                return this.info.funcid2name.find(item => item.id === funcId)
            },
            show() {
                this.dialogVisible = true;
            },
            // 根据所选的模式, 构造请求的bwinfo参数
            bwinfoParam() {
                let bwinfoParam = {
                    topicid: this.info.bwinfo.topicid,
                    wblist: []
                }
                switch (this.form.mode) {
                    // 无筛选时, wblish为空
                    case 'none':
                        break
                    case 'outOf':
                        // 全部下架时,将wblish[0]的flag置为黑名单
                        bwinfoParam.wblist.push({
                            flag: this.info.XMBookBWInfoFlag.kXMBookBWInfoFlagIsBlack,
                        })
                        break
                    case 'bindTag':
                        // 全部通过时,将wblish[0]的flag置为白名单,同时将所需的tag加入
                        bwinfoParam.wblist.push({
                            flag: this.info.XMBookBWInfoFlag.kXMBookBWInfoFlagIsWhite,
                            autotags: this.autoTagsHandler(this.form.searchTagForBindTag),
                        })
                        break
                    case 'custom':
                        // 自定义规则,需要多组wblish[n], 若flag为黑名单,不需要condtions和autotags,为白名单时需要condtions和autotags
                        this.form.wblist.map(wbItem => {
                            bwinfoParam.wblist.push({
                                flag: wbItem.flag,
                                autotags: this.autoTagsHandler(wbItem.searchTagForCustom),
                                condtions: wbItem.condtions
                            })
                        })
                        break
                }
                return bwinfoParam
            },
            // 点击确定,发送请求
            confirm() {
                if (this.checkForm()) {
                    let param = {
                        func: 21,
                        updatebwinforeq: JSON.stringify({
                            bwinfo: this.bwinfoParam()
                        })
                    }
                    this.$parent.sendUpdateMedia(param)
                    this.dialogVisible = false;
                }
            },
            // 传入search组件的tags, 返回autoTags
            autoTagsHandler(searchTags) {
                let selected2Ids = (selected) => {
                    if (!selected) {
                        return []
                    }
                    let tagIds = [];
                    selected.map(item => {
                        tagIds.push(item.id)
                    })
                    return tagIds
                }

                let tags = {leveldatas: []}
                tags.leveldatas.push({
                    level: 1,
                    tagids: selected2Ids(searchTags.searchTag1.selected)
                })
                tags.leveldatas.push({
                    level: 2,
                    tagids: selected2Ids(searchTags.searchTag2.selected)
                })
                return tags
            },
            checkForm() {
                if (['none', 'outOf', 'bindTag'].includes(this.form.mode)) {
                    return true
                } else if (this.form.mode === 'custom') {
                    if (!this.form.wblist || this.form.wblist.length < 1) {
                        this.$message.error('自定义规则不能为空!');
                        return false;
                    } else {
                        return this.form.wblist.every(wbItem => {
                            if (!wbItem.flag || wbItem.flag === 0) {
                                this.$message.error('未选择执行操作!');
                                return false
                            } else if (!wbItem.condtions || wbItem.condtions.length < 1) {
                                this.$message.error('条件不能为空!');
                                return false
                            }
                            return wbItem.condtions.every(condItem => {
                                if (!condItem.fieldid) {
                                    this.$message.error('未选择条件字段!');
                                    return false
                                } else if (!condItem.funcid) {
                                    this.$message.error('未选择条件功能!');
                                    return false;
                                } else {
                                    return true
                                }
                            })
                        })
                    }
                }
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
            list2Map(list, key = 'id') {
                let map = new Map()
                for (let item of list) {
                    map.set(item[key], item)
                }
                return map
            },
            /**
             * 传入autoTags,返回search组件需要的searchTag
             * @param autoTags
             * @param level
             * @return {{placeholder: string, tagType: string, width: number, selected: *, allDatas: *}}
             */
            levelTag2searchTag(autoTags, level) {
                let searchTag = {
                    placeholder: `${level}级标签`,
                    tagType: level === 1 ? 'warning' : 'success',
                    width: 200,
                    selected: this.tagidsHandler(autoTags, level),
                    allDatas: this[`allTag${level}`],
                }
                return searchTag
            },

            // 编辑之前初始化数据
            updateInfo() {
                // 判断筛选方式
                if (!this.info.bwinfo || !this.info.bwinfo.wblist || this.info.bwinfo.wblist.length < 1) {
                    this.form.mode = 'none'
                    this.form.wblist = []
                } else if (this.info.bwinfo.wblist.length === 1 && (!this.info.bwinfo.wblist[0].condtions || this.info.bwinfo.wblist[0].condtions.length < 1)) {
                    if (this.info.bwinfo.wblist[0].flag === this.info.XMBookBWInfoFlag.kXMBookBWInfoFlagIsBlack) {
                        this.form.mode = 'outOf'
                        this.form.wblist = []
                    } else {
                        this.form.mode = 'bindTag'
                        this.form.wblist = this.info.bwinfo.wblist
                    }

                } else {
                    this.form.mode = 'custom'
                    this.form.wblist = this.info.bwinfo.wblist
                }

                // searchTagForBindTag初始化, 如果是bindTag模式, 将wblist清空以避免影响后续的自定义
                let bindAutotags = null
                if (this.form.mode === 'bindTag' && this.info.bwinfo.wblist[0].autotags) {
                    bindAutotags = cloneDeep(this.info.bwinfo.wblist[0].autotags)
                    this.removeRule(0)
                }
                this.form.searchTagForBindTag.searchTag1 = this.levelTag2searchTag(bindAutotags, 1)
                this.form.searchTagForBindTag.searchTag2 = this.levelTag2searchTag(bindAutotags, 2)


                // 将custom模式的wblist中的searchTagForCustom初始化
                for (let wbItem of this.form.wblist) {
                    wbItem.searchTagForCustom = {
                        searchTag1: this.levelTag2searchTag(wbItem.autotags, 1),
                        searchTag2: this.levelTag2searchTag(wbItem.autotags, 2)
                    }
                }
            },
            addRule() {
                if (!this.form.wblist) {
                    this.form.wblist = []
                }
                this.form.wblist.push({
                    bwid: '',	 // 唯一id
                    flag: '',	 // 标志位 XMBookBWInfoFlag
                    autotags: {  // 标签集合
                        leveldatas: [
                            {
                                level: 1,             // 文章属于第level级标签
                                tagids: []    // 文章囊括的标签名
                            },
                            {
                                level: 2,             // 文章属于第level级标签
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
                    ],
                    searchTagForCustom: {
                        searchTag1: this.levelTag2searchTag([], 1),
                        searchTag2: this.levelTag2searchTag([], 2)
                    }
                })
            },
            removeRule(wbIndex) {
                this.form.wblist.splice(wbIndex, 1)
            },
            addCondition(wbitem) {
                if (!wbitem.condtions) {
                    wbitem.condtions = []
                }
                wbitem.condtions.push({
                    fieldid: '',						// 匹配字段名称 XMBookBWInfoCondFieldID
                    fieldval_intmin: '',				// 匹配数值最小
                    fieldval_intmax: '',				// 匹配数值最大
                    fieldval_str: '',				// 匹配字符串
                    funcid: '',						// 匹配方法 XMBookBWInfoCondFuncID
                })
            },
            removeCondition(wbIndex, conditionIndex) {
                this.form.wblist[wbIndex].condtions.splice(conditionIndex, 1)
                // 如果把最后一条condition删除, 那么同时去掉此Rule
                if (this.form.wblist[wbIndex].condtions.length === 0) {
                    this.removeRule(wbIndex)
                }
            }
        },
        computed: {
            allTag1() {
                let allDatas = []
                this.info.taglist.taglist1.map(item => {
                    allDatas.push({
                        id: item.id,
                        value: item.name
                    })
                })
                return allDatas
            },
            allTag2() {
                let allDatas = []
                this.info.taglist.taglist2.map(item => {
                    allDatas.push({
                        id: item.id,
                        value: item.name
                    })
                })
                return allDatas
            }
        }
    }
</script>

