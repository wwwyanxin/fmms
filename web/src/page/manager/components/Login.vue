<template>
    <div style="text-align: center;">
        <el-tag style="margin: 20px;display: block;width: 100px;">{{'管理员登录'}}</el-tag>
        <el-card shadow="always" style="width:500px;display:inline-block">
            <div class="container" style="margin-right: 35px;">
                <div class="login">
                    <el-form :model="loginForm" size="mini" status-icon :rules="loginRules" ref="loginForm"
                             label-width="100px"
                             class="demo-ruleForm">
                        <el-form-item label="账号" prop="account">
                            <el-input type="text" v-model="loginForm.account"></el-input>
                        </el-form-item>
                        <el-form-item label="密码" prop="password">
                            <el-input type="password" v-model="loginForm.password"></el-input>
                        </el-form-item>
                        <el-form-item>
                            <el-button type="primary" @click="submitForm('loginForm')">提交</el-button>
                            <el-button @click="resetForm('loginForm')">重置</el-button>
                        </el-form-item>
                    </el-form>
                </div>
            </div>
        </el-card>
    </div>
</template>

<script>
    import Api from '@/service/api.js'
    import global from '@/service/global'

    export default {
        name: "Login",
        data() {
            var validateLoginPass = (rule, value, callback) => {
                if (value === '') {
                    callback(new Error('请输入密码'));
                }
                callback();
            };
            var validateLoginAccount = (rule, value, callback) => {
                if (!value) {
                    return callback(new Error('请输入账号'));
                }
                callback();
            };
            return {
                loginForm: {
                    account: '',
                    password: '',
                },
                loginRules: {
                    account: [
                        {validator: validateLoginAccount, trigger: 'blur'}
                    ],
                    password: [
                        {validator: validateLoginPass, trigger: 'blur'}
                    ],
                }
            };
        },
        methods: {
            submitForm(formName) {
                this.$refs[formName].validate(async (valid) => {
                    if (valid) {
                        //登录
                        const res = await Api.post('manager_login', {
                            account: this.loginForm.account,
                            password: this.loginForm.password,
                        })
                        if (res.status) {
                            global.get('app').$message({
                                type: 'success',
                                message: '登录成功'
                            })
                            global.set("manager",res.data);
                            this.$router.push("/");
                        } else {
                            global.get('app').$message({
                                type: 'error',
                                message: '账号或密码错误'
                            })
                        }

                    } else {
                        console.log('error submit!!');
                        return false;
                    }
                });
            },
            resetForm(formName) {
                this.$refs[formName].resetFields();
            },
        }
    }
</script>

<style scoped>

</style>