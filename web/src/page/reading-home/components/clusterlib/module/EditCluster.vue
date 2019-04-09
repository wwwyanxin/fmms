<template>
    <el-dialog title="编辑卡片" :visible.sync="dialogVisible" width="55%">
        <el-form>
            <el-form-item label="卡片名">
                <el-input v-model="form.name" auto-complete="off" clearable
                          style="max-width:300px;"></el-input>
            </el-form-item>
            <el-form-item label="关联1级标签">
                <SearchAppend :info="searchTag1"></SearchAppend>
            </el-form-item>
            <el-form-item label="推荐文章数量">
                <template slot-scope="scope">
                    <el-input-number
                            style="width: 88px;"
                            size="mini"
                            v-model="form.articlenum"
                            :step="1"
                            :precision="0"
                            :min="0"
                    ></el-input-number>
                </template>
            </el-form-item>
            <el-form-item label="状态设置为">
                <el-radio-group v-model="form.flag" size="small">
                    <!--未发布状态目前字段是空的-->
                    <el-radio-button :label="0">未发布</el-radio-button>
                    <el-radio-button :label="clusterFlag.eXMBookClusterInfoFlagIsRuning">运营中</el-radio-button>
                    <el-radio-button :label="clusterFlag.eXMBookClusterInfoFlagIsOffTheShelved">已下线</el-radio-button>
                </el-radio-group>
            </el-form-item>
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
        name: "EditCluster",
        components: {SearchAppend},
        props: {
            info: {
                taglist: {
                    taglist1: [],
                },
                selected: {
                    tagSelect1: [],
                },
                id: '',
                name: '',
                flag: '',
                sortid: '',
                articlenum: ''
            },
            clusterFlag: {
                eXMBookClusterInfoFlagIsRuning: 0x01, // 运营中
                eXMBookClusterInfoFlagIsOffTheShelved: 0x02, // 下线了
            }
        },
        data() {
            return {
                dialogVisible: false,
                form: {
                    name: '',
                    flag: '',
                    sortid: '',
                    articlenum: '',
                },

                searchTag1: {
                    placeholder: '查找标签',
                    tagType: 'warning',
                    selected: [],
                    allDatas: [],
                },
            }
        },
        mounted() {
            this.updateInfo()
        },
        watch: {
            info: {
                deep: true,
                handler: function () {
                    this.updateInfo()
                }
            }
        },
        methods: {
            show() {
                this.dialogVisible = true;
            },
            confirm() {
                if (!this.checkName()) {
                    return
                }
                this.$bus.$emit('clusterHandler', {
                    func: 'sendUpdateCluster',
                    args: {
                        func: 8,
                        updateclusterinforeq: JSON.stringify({
                            clusterinfo: {
                                id: this.info.id,
                                name: this.form.name,
                                flag: this.form.flag,
                                sortid: this.info.sortid,
                                articlenum: this.info.articlenum,
                                tags: this.xmtagsHandler(),
                            }
                        })
                    },
                });
                this.dialogVisible = false;
                // 清空选择
                this.searchTag1.selected = []
            },
            checkName() {
                if (this.form.name.length > 5) {
                    this.$message({
                        type: 'error',
                        message: '名称长度不应超过5'
                    });
                    return false
                } else if (this.form.name.length < 1) {
                    this.$message({
                        message: '名称不能为空',
                        type: 'error'
                    })
                    return false
                }
                return true
            },
            updateInfo() {
                this.form = this.info ? this.info : ''
                this.searchTag1.selected = cloneDeep(this.info.selected.tagSelect1 || [])
                this.searchTag1.allDatas = []
                this.info.taglist.taglist1.map(item => {
                    this.searchTag1.allDatas.push({
                        id: item.id,
                        value: item.name
                    })
                })
            },
            xmtagsHandler() {
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

                let xmtags = {leveldatas: []}
                xmtags.leveldatas.push({
                    level: 1,
                    tagids: selected2Ids(this.searchTag1.selected)
                })
                return xmtags
            },
        }
    }
</script>

<style scoped>

</style>
