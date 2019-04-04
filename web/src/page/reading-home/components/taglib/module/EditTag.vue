<template>
    <div>
        <el-dialog title="管理标签" :visible.sync="dialogFormVisible" width="55%">
            <el-form :model="form">
                <el-form-item label="标签名" :label-width="formLabelWidth">
                    <el-input v-model="form.name" auto-complete="off" clearable
                              style="max-width:300px;"></el-input>
                </el-form-item>
                <el-form-item label="标签类型" :label-width="formLabelWidth">
                    <el-tag type="danger" hit>
                        {{tagType}}
                    </el-tag>
                </el-form-item>
                <el-form-item v-if="info.tagInfo.father.level ===1 && info.func==='editTag'" label="关联二级标签"
                              :label-width="formLabelWidth">
                    <SearchAppend :info="searchInfoTag"></SearchAppend>
                </el-form-item>
            </el-form>
            <div slot="footer" class="dialog-footer">
                <el-button @click="dialogFormVisible = false">取 消</el-button>
                <el-button type="primary" @click="confirmEdit">确 定</el-button>
            </div>
        </el-dialog>
    </div>
</template>

<script>
    import SearchAppend from "@/components-ui/searchAppend/SearchAppend";
    import {cloneDeep} from '@/lib/util'

    export default {
        name: "EditTag",
        components: {SearchAppend},
        props: {
            info: {}
        },
        data() {
            return {
                dialogFormVisible: false,
                formLabelWidth: '100px',
                form: {},
                searchInfoTag: {
                    placeholder: '查找标签',
                    tagType: 'success',
                    selected: [],
                    allDatas: []
                }
            };
        },
        watch: {
            info: {
                deep: true,
                handler: function () {
                    if (this.info.func === 'editTag') {
                        if (this.info.tagInfo.father.level === 1) {
                            this.form = this.info.tagInfo.father
                            this.searchInfoTag.selected = cloneDeep(this.info.tagInfo.childlist || [])
                            this.searchInfoTag.allDatas = this.info.allTags2
                        } else if (this.info.tagInfo.father.level === 2) {
                            this.form = this.info.tagInfo.father
                        }
                    } else if (this.info.func === 'addTag') {
                        this.form = this.info.tagInfo.father
                        this.searchInfoTag.selected = cloneDeep(this.info.tagInfo.childlist || [])
                        this.searchInfoTag.allDatas = this.info.allTags2
                    }
                }
            }
        },
        methods: {
            // 对添加和修改标签的操作都弹出box
            show() {
                if (this.info.func === 'addTag') {
                    this.dialogFormVisible = true;
                } else if (this.info.func === 'editTag') {
                    this.dialogFormVisible = true;
                }
            },
            // 添加或者修改标签, 点击确认触发
            confirmEdit() {
                if (!this.checkName()) {
                    return
                }

                if (this.info.func === 'editTag') {
                    let param = this.editParam();
                    this.$parent.updateTag(param);
                } else if (this.info.func === 'addTag') {
                    this.$parent.addTag(this.form);
                }
                this.dialogFormVisible = false;

            },
            // 名字不能为空
            checkName() {
                if (!this.form.name || this.form.name.length < 1) {
                    this.$message({
                        message: '标签名不能为空',
                        type: 'error'
                    })
                    return false
                }
                return true
            },
     /*       searchFilter(queryString, field) {
                return (state) => {
                    return (state[field].toLowerCase().indexOf(queryString.toLowerCase()) !== -1);
                };
            },*/
            /**
             * 关联二级标签的操作
             * 1.如果有新增关联,名字就加childname里
             * 2.如果有删除,就把newchildlist里的id减去
             * @return {{id: string, newtagname: string, addchildnames: Array, newchildlist: Array}}
             */
            editParam() {
                let param = {
                    id: this.info.tagInfo.father.id,
                    newtagname: this.form.name,
                    addchildnames: [],
                    newchildlist: []
                }
                if (this.searchInfoTag.selected && this.searchInfoTag.selected.length > 0) {
                    for (let item of this.searchInfoTag.selected) {
                        // 如果此标签是之前选过的,存入newchildlist中
                        if (this.hasSelectedName(item.name)) {
                            param.newchildlist.push(item.id);
                        } else {
                            // 否则此标签是新选中的, 放入addchildnames
                            param.addchildnames.push(item.name)
                        }
                    }
                }

                return param
            },
            // 判断此标签是否是之前选过的
            hasSelectedName(name) {
                if (!this.info.tagInfo.childlist)
                    return false
                for (let item of this.info.tagInfo.childlist) {
                    if (item.name === name) {
                        return true
                    }
                }
                return false
            }
        },
        computed: {
            tagType() {
                return this.info.tagInfo.father.level + '级标签'
            }
        }
    }
</script>

<style scoped>

</style>
