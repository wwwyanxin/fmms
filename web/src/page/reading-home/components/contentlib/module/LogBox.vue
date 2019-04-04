<template>
    <el-dialog title="打分管理" :visible.sync="dialogVisible" width="55%">
        <el-table
                :data="tableData"
                stripe
                style="width: 100%">
            <el-table-column
                    prop="date"
                    label="ID"
                    width="180">
            </el-table-column>
            <el-table-column
                    prop="name"
                    label="时间"
                    width="180">
            </el-table-column>
            <el-table-column
                    prop="address"
                    label="打分人">
            </el-table-column>
            <el-table-column
                    prop="address"
                    label="操作内容">
            </el-table-column>
        </el-table>
        <div slot="footer" class="dialog-footer">
            <el-button @click="dialogVisible = false">取 消</el-button>
            <el-button type="primary" @click="confirmEdit">确 定</el-button>
        </div>
    </el-dialog>
</template>

<script>
    export default {
        name: "LogBox",
        data() {
            return {
                dialogVisible: false,
                tableData: [{
                    date: '2016-05-02',
                    name: '王小虎',
                    address: '上海市普陀区金沙江路 1518 弄'
                }, {
                    date: '2016-05-04',
                    name: '王小虎',
                    address: '上海市普陀区金沙江路 1517 弄'
                }, {
                    date: '2016-05-01',
                    name: '王小虎',
                    address: '上海市普陀区金沙江路 1519 弄'
                }, {
                    date: '2016-05-03',
                    name: '王小虎',
                    address: '上海市普陀区金沙江路 1516 弄'
                }]
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
