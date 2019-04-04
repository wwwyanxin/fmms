<template>
    <div>
        <el-button type="success" size="mini" round @click="addTagBox()">新增{{this.tagLevel}}级标签</el-button>
        <TagTable :fatherlist="fatherlist" :tagLevel="tagLevel" v-loading="tableLoading"></TagTable>
        <EditTag ref="editTag" :info="editInfo"></EditTag>
    </div>
</template>

<script>
    import TagTable from '../TagTable'
    import EditTag from '../EditTag'
    import Api from '@/service/api.js'
    import {cloneDeep} from '@/lib/util'

    export default {
        name: "Tag2",
        components: {TagTable, EditTag},
        data() {
            return {
                editInfo: {
                    tagInfo: {
                        father:{
                            id: '',
                            createtime: '',
                            name: '',
                            fid: '',
                            level: '',
                        },
                        childlist:[]
                    },
                    func: '',
                },
                fatherlist: [],
                tagLevel: 2,
                tableLoading: true,
            }
        },
        mounted(){
            this.updateData()
        },
        methods: {
            async updateData() {
                const res = await Api.get('/oa/call', {
                    func: 12,
                    cgigettagfatherlistreq: JSON.stringify({
                        level: this.tagLevel
                    })
                })
                this.fatherlist = res.fatherlist

                this.tableLoading = false
            },
            async addTag(param) {
                if (this.checkName(param)) {
                    await Api.post('/oa/call', {
                        func: 9,
                        addtaginforeq: JSON.stringify({
                            name: param.name,
                            level: this.tagLevel,

                        })
                    })
                    this.updateData()
                }
            },
            async deleteTag(param) {
                await Api.post('/oa/call', {
                    func: 10,
                    deletetaginforeq: JSON.stringify({
                        ...param
                    })
                })
                this.updateData()
            },
            async updateTag(param) {
                if (this.checkName(param)) {
                    await Api.post('/oa/call', {
                        func: '13',
                        cgiupdatetaginforeq: JSON.stringify({
                            ...param
                        })
                    })
                    this.updateData()
                }
            },
            updateTagBox(index, row) {
                this.editInfo.tagInfo = cloneDeep(this.fatherlist[index])
                this.editInfo.func = 'editTag'
                this.$refs.editTag.show()
            },
            addTagBox() {
                this.editInfo.tagInfo = {
                    father: {
                        id: '',
                        createtime: '',
                        name: '',
                        fid: '',
                        level: this.tagLevel,
                    },
                    childlist: []
                }
                this.editInfo.func = 'addTag'
                this.$refs.editTag.show()
            },
            checkName(param) {
                const has = this.fatherlist.some(item => {
                    if (item.father.name === param.newtagname || item.father.name === param.name) {
                        if (param.id) {
                            return item.father.id !== param.id;
                        } else {
                            return true
                        }
                    }
                })
                if (has) {
                    this.$message({
                        type: 'error',
                        message: `标签: ${param.newtagname || param.name} 已存在!`
                    })
                }
                return !has
            }
        }
    }
</script>

<style scoped>

</style>
