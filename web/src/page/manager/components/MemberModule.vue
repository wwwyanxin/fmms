<template>
    <div>
        <div class="table">
            <el-table
                    :data="memberList"
                    height="600"
                    border
                    stripe
                    style="width: 100%">
                <el-table-column
                        prop="id"
                        label="ID"
                        width="80">
                </el-table-column>
                <el-table-column
                        prop="account"
                        label="账号"
                        >
                </el-table-column>
                <el-table-column
                        prop="name"
                        label="姓名"
                        >
                </el-table-column>
                <el-table-column
                        prop="sex"
                        label="性别"
                        width="80"
                >
                    <template slot-scope="scope">
                        {{scope.row.sex === 'female' ? '男':'女'}}
                    </template>
                </el-table-column>
                <el-table-column
                        prop="start_date"
                        label="注册日期"
                >
                    <template slot-scope="scope">
                        <span style="margin-left: 10px">{{ dateFormat(scope.row.start_date) }}</span>
                    </template>
                </el-table-column>
                <el-table-column
                        prop="end_date"
                        label="到期日期"
                >
                    <template slot-scope="scope">
                        <i class="el-icon-time"></i>
                        <span style="margin-left: 10px">{{ scope.row.end_date === -1 ?"未缴费":dateFormat(scope.row.end_date) }}</span>
                    </template>
                </el-table-column>
                <el-table-column label="操作" width="75">
                    <template slot-scope="scope">
                        <el-button
                                size="mini"
                                type="danger"
                                @click="handleEdit(scope.$index, scope.row)">编辑
                        </el-button>
                    </template>
                </el-table-column>
            </el-table>
        </div>
        <div class="edit">
            <el-dialog title="编辑会员" :visible.sync="dialogVisible" width="55%">
                <el-form>
                    <el-form-item label="姓名">
                        <el-input v-model="form.name" clearable
                                  style="max-width:300px;"></el-input>
                    </el-form-item>
                    <el-form-item label="性别">
                        <el-radio-group v-model="form.sex" size="small">
                            <el-radio-button :label="'female'">男</el-radio-button>
                            <el-radio-button :label="'male'">女</el-radio-button>
                        </el-radio-group>
                    </el-form-item>
                </el-form>
                <div slot="footer" class="dialog-footer">
                    <el-button @click="dialogVisible = false">取 消</el-button>
                    <el-button type="primary" @click="formConfirm">确 定</el-button>
                </div>
            </el-dialog>

        </div>
    </div>
</template>

<script>
    import Api from '@/service/api.js'
    import {cloneDeep} from '@/lib/util'
    import global from '@/service/global'
    import dayjs from 'dayjs'

    export default {
        name: "MemberModule",
        data(){
            return {
                dialogVisible:false,
                memberList:[],
                form:{}
            }
        },
        mounted(){
            this.pullMemberList();
        },
        methods:{
            async pullMemberList(){
                const res = await Api.get("member_list");
                this.memberList = res.data.memberList;
            },
            dateFormat(dateTime){
                return dayjs(dateTime * 1000).format('YYYY年MM月DD日')
            },
            handleEdit(index, row) {
                this.form = cloneDeep(this.memberList[index])
                this.dialogVisible = true
            },
            checkItem(form, field, errorMessage) {
                if (!form[field]) {
                    global.get('app').$message({
                        type: 'error',
                        message: errorMessage
                    })
                    return false;
                } else {
                    return true;
                }
            },
            checkForm() {
                if (this.checkItem(this.form, 'name', '未填写姓名')
                ) {
                    return true;
                } else {
                    return false;
                }
            },
            async formConfirm(){
                if (!this.checkForm()) {
                    return
                }
                await Api.post("member_update",this.form);
                this.pullMemberList();
                this.dialogVisible = false
            }
        }
    }
</script>

<style scoped>

</style>