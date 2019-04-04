<template>
    <el-dialog title="内容标签管理" :visible.sync="dialogVisible" width="55%">
        <el-form>
            <el-form-item label="1级标签" >
                <SearchAppend :info="searchTag1"></SearchAppend>
            </el-form-item>
        </el-form>
        <el-form>
            <el-form-item label="2级标签">
                <SearchAppend :info="searchTag2"></SearchAppend>
            </el-form-item>
        </el-form>
        <div slot="footer" class="dialog-footer">
            <el-button @click="dialogVisible = false">取 消</el-button>
            <el-button type="primary" @click="confirmEdit">确 定</el-button>
        </div>
    </el-dialog>
</template>

<script>
    import SearchAppend from "@/components-ui/searchAppend/SearchAppend";
    import {cloneDeep} from '@/lib/util'

    export default {
        name: "ContentTagBox",
        components: {SearchAppend},
        props:{
            contentTagInfo:{  // 内容打标box和table
                taglist:{
                    taglist1:[],
                    taglist2:[]
                },
                selected:{
                    tagSelect1:[],
                    tagSelect2:[],
                },
            },
            articleInfo:{}
        },
        data() {
            return {
                dialogVisible: false,
                searchTag1:{
                    placeholder:'查找标签',
                    tagType:'warning',
                    selected:[],
                    allDatas: [],
                },
                searchTag2:{
                    placeholder:'查找标签',
                    tagType:'success',
                    selected:[],
                    allDatas: [],
                }
            }
        },
        mounted(){
          this.updateTagInfo()
        },
        watch:{
            contentTagInfo: {
                deep: true,
                handler: function () {
                    this.updateTagInfo()
                }
            }
        },
        methods: {
            show() {
                this.dialogVisible = true;
            },
            xmtagsHandler() {
                let selected2Ids = (selected) =>{
                    if (!selected) {
                        return []
                    }
                    let tagIds = [];
                    selected.map(item=>{
                        tagIds.push(item.id)
                    })
                    return tagIds
                }

                let xmtags = {leveldatas:[]}
                xmtags.leveldatas.push({
                    level:1,
                    tagids:selected2Ids(this.searchTag1.selected)
                })
                xmtags.leveldatas.push({
                    level:2,
                    tagids:selected2Ids(this.searchTag2.selected)
                })
                return xmtags
            },
            confirmEdit() {
                this.$bus.$emit('contentHandler', {
                    func:'sendUpdateArticle',
                    args:{
                        func: 3,
                        updateArticlereq:JSON.stringify({
                            topicid: this.articleInfo.topicid,
                            articleid: this.articleInfo.articleid,
                            xmtags:this.xmtagsHandler(),
                            // xmauthor: this.articleInfo.xmauthor,
                        })
                    },
                })
                this.dialogVisible = false;
                // 清空选择
                this.searchTag1.selected = []
                this.searchTag2.selected = []
            },
            updateTagInfo() {
                this.searchTag1.selected = cloneDeep(this.contentTagInfo.selected.tagSelect1 || [])
                this.searchTag2.selected = cloneDeep(this.contentTagInfo.selected.tagSelect2 || [])
                this.searchTag1.allDatas = []
                this.searchTag2.allDatas = []
                this.contentTagInfo.taglist.taglist1.map(item=>{
                    this.searchTag1.allDatas.push({
                        id:item.id,
                        value:item.name
                    })
                })
                this.contentTagInfo.taglist.taglist2.map(item=>{
                    this.searchTag2.allDatas.push({
                        id:item.id,
                        value:item.name
                    })
                })
            }
        }
    }
</script>

<style scoped>

</style>
