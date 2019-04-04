<template>
    <el-dialog title="分类标签管理" :visible.sync="dialogVisible" width="55%">
        <SearchAppend :info="searchInfo"></SearchAppend>
        <div slot="footer" class="dialog-footer">
            <el-button @click="dialogVisible = false">取 消</el-button>
            <el-button type="primary" @click="confirmEdit">确 定</el-button>
        </div>
    </el-dialog>
</template>

<script>
    import SearchAppend from "../../../../../components-ui/searchAppend/SearchAppend";
    export default {
        name: "CategoryTagBox",
        components: {SearchAppend},
        data() {
            return {
                dialogVisible: false,
                searchInfo:{
                    placeholder:'查找标签',
                    tagType:'warning',
                    selected:[
                        {
                            name:'1'
                        },
                        {
                            name:'2'
                        }
                    ],
                    allDatas:
                        [
                            {value: "壹分米客家传统调制米粉(天山店)", "address": "天山西路428号"},
                            {value: "福荣祥烧腊（平溪路店）", "address": "上海市长宁区协和路福泉路255弄57-73号"},
                            {value: "速记黄焖鸡米饭", "address": "上海市长宁区北新泾街道金钟路180号1层01号摊位"},
                            {value: "红辣椒麻辣烫", "address": "上海市长宁区天山西路492号"},
                            {value: "(小杨生煎)西郊百联餐厅", "address": "长宁区仙霞西路88号百联2楼"},
                            {value: "阳阳麻辣烫", "address": "天山西路389号"},
                            {value: "南拳妈妈龙虾盖浇饭", "address": "普陀区金沙江路1699号鑫乐惠美食广场A13"}
                        ],
                }
            }
        },
        methods: {
            show() {
                this.dialogVisible = true;
            },
            confirmEdit() {
                this.dialogVisible = false;
            },
        }
    }
</script>

<style scoped>

</style>
