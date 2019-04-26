<template>
    <div>
        <div class="add">
            <el-button type="warning" size="mini" @click="handleAdd()">添加教练</el-button>
        </div>
        <div class="table">
            <el-table
                    :data="coachList"
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
                        prop="name"
                        label="姓名"
                        width="120"
                >
                </el-table-column>
                <el-table-column
                        prop="sex"
                        label="性别"
                        width="80"
                >
                    <template slot-scope="scope">
                        {{scope.row.sex === 'male' ? '男':'女'}}
                    </template>
                </el-table-column>
                <el-table-column
                        prop="entry_date"
                        label="入职日期"
                        width="200"
                >
                    <template slot-scope="scope">
                        <i class="el-icon-time"></i>
                        <span style="margin-left: 10px">{{ dateFormat(scope.row.entry_date) }}</span>
                    </template>
                </el-table-column>
                <el-table-column
                        prop="introduction"
                        label="简介"
                >
                </el-table-column>
                <el-table-column
                        prop="status"
                        label="状态"
                        width="80"
                >
                    <template slot-scope="scope">
                        {{scope.row.status === 'on_work' ? '在职':'已离职'}}
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
            <el-dialog title="编辑教练" :visible.sync="dialogVisible" width="55%">
                <el-form>
                    <el-form-item label="姓名">
                        <el-input v-model="form.name" clearable
                                  style="max-width:300px;"></el-input>
                    </el-form-item>
                    <el-form-item label="性别">
                        <el-radio-group v-model="form.sex" size="small">
                            <el-radio-button :label="'male'">男</el-radio-button>
                            <el-radio-button :label="'female'">女</el-radio-button>
                        </el-radio-group>
                    </el-form-item>
                    <el-form-item label="状态">
                        <el-radio-group v-model="form.status" size="small">
                            <el-radio-button :label="'on_work'">在职</el-radio-button>
                            <el-radio-button :label="'off_work'">已离职</el-radio-button>
                        </el-radio-group>
                    </el-form-item>
                    <el-form-item label="简介">
                        <el-input v-model="form.introduction"
                                  type="textarea"
                                  :autosize="{ minRows: 3, maxRows: 6}"
                                  placeholder="请输入内容"
                                  style="max-width:500px;"></el-input>
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
        name: "CoachModule",
        data() {
            return {
                dialogVisible: false,
                model: '',  // add,update
                coachList: [],
                form: {}
            }
        },
        mounted() {
            this.pullCoachList();
        },
        methods: {
            async pullCoachList() {
                const res = await Api.get("coach_list");
                this.coachList = res.data.coachList;
            },
            dateFormat(dateTime) {
                return dayjs(dateTime * 1000).format('YYYY年MM月DD日')
            },
            handleEdit(index, row) {
                this.form = cloneDeep(this.coachList[index])
                this.model = 'update';
                this.dialogVisible = true
            },
            handleAdd() {
                this.form = {status: 'on_work'};
                this.model = 'add';
                this.dialogVisible = true;
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
                if (this.checkItem(this.form, 'name', '未填写姓名') &&
                    this.checkItem(this.form, 'sex', '未选择性别') &&
                    this.checkItem(this.form, 'introduction', '请填写简介')
                ) {
                    return true;
                } else {
                    return false;
                }
            },
            async formConfirm() {
                if (!this.checkForm()) {
                    return
                }
                await Api.post(`coach_${this.model}`, this.form);
                this.pullCoachList();
                this.dialogVisible = false
            }
        }
    }
</script>

<style scoped>

</style>