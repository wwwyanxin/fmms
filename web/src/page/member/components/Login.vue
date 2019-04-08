<template>
    <div style="text-align: center;">
        <el-tag style="margin: 20px;display: block;width: 100px;">{{toggle=='login'?'会员登录':'会员注册'}}</el-tag>
        <el-card shadow="always" style="width:500px;display:inline-block">
            <div class="container" style="margin-right: 35px;">
                <div v-if="toggle==='register'" class="register">
                    <el-form :model="registerForm" size="mini" status-icon :rules="registerRules" ref="registerForm" label-width="100px"
                             class="demo-ruleForm">
                        <el-form-item label="账号" prop="registerAccount">
                            <el-input type="text" v-model="registerForm.registerAccount"></el-input>
                        </el-form-item>
                        <el-form-item label="密码" prop="registerPassword">
                            <el-input type="password" v-model="registerForm.registerPassword"></el-input>
                        </el-form-item>

                        <el-form-item v-if="false">
                        </el-form-item>

                        <el-form-item label="再次输入密码" prop="registerPassword2">
                            <el-input type="password" v-model="registerForm.registerPassword2"></el-input>
                        </el-form-item>

                        <el-form-item label="姓名" prop="name">
                            <el-input type="text" v-model="registerForm.name"></el-input>
                        </el-form-item>
                        <el-form-item label="性别" prop="sex">
                            <el-radio v-model="registerForm.sex" label="male">男</el-radio>
                            <el-radio v-model="registerForm.sex" label="female">女</el-radio>
                        </el-form-item>
                        <el-form-item>
                            <el-button type="primary" @click="submitForm('registerForm')">提交</el-button>
                            <el-button @click="resetForm('registerForm')">重置</el-button>
                            <el-button @click="()=>toggle = 'login'" type="success" style="margin-left: 120px;">去登录</el-button>
                        </el-form-item>
                    </el-form>
                </div>
                <div v-else-if="toggle==='login'" class="login">
                    <el-form :model="loginForm" size="mini" status-icon :rules="loginRules" ref="loginForm" label-width="100px"
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
                            <el-button @click="()=>toggle = 'register'" type="success" style="margin-left: 120px;">去注册</el-button>
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
            var validateRegisterPass = (rule, value, callback) => {
                if (value === '') {
                    callback(new Error('请输入密码'));
                } else {
                    if (this.registerForm.checkPass !== '') {
                        this.$refs.registerForm.validateField('registerPassword2');
                    }
                    callback();
                }
            };
            var validateRegisterPass2 = (rule, value, callback) => {
                if (value === '') {
                    callback(new Error('请再次输入密码'));
                } else if (value !== this.registerForm.registerPassword) {
                    callback(new Error('两次输入密码不一致!'));
                } else {
                    callback();
                }
            };
            var validateRegisterAccount = async(rule,value,callback) => {
                if (!value) {
                    return callback(new Error('账号不能为空'));
                }
                const res = await Api.get('/fmms/cgi-bin/hello_world.cgi/member_register_check_account', {
                    account:value
                })
                if(!res.status){
                    return callback(new Error('此账号已被注册'));
                }else{
                    callback();
                }
            };
            var validateRegisterName = (rule,value,callback) => {
                if (!value) {
                    return callback(new Error('姓名不能为空'));
                }
                callback();
            };
            var validateRegisterSex = (rule,value,callback) => {
                if (!value) {
                    return callback(new Error('性别不能为空'));
                }
                callback();
            };
            var validateLoginPass = (rule, value, callback) => {
                if (value === '') {
                    callback(new Error('请输入密码'));
                }
                callback();
            };
            var validateLoginAccount = (rule,value,callback) => {
                if (!value) {
                    return callback(new Error('请输入账号'));
                }
                callback();
            };
            return {
                toggle:"login",
                registerForm: {
                    registerAccount:'',
                    registerPassword:'',
                    registerPassword2: '',
                    name:'',
                    sex:''

                },
                registerRules: {
                    registerAccount: [
                        {validator: validateRegisterAccount, trigger: 'blur'}
                    ],
                    registerPassword: [
                        {validator: validateRegisterPass, trigger: 'blur'}
                    ],
                    registerPassword2: [
                        {validator: validateRegisterPass2, trigger: 'blur'}
                    ],
                    name: [
                        {validator: validateRegisterName, trigger: 'blur'}
                    ],
                    sex: [
                        {validator: validateRegisterSex, trigger: 'blur'}
                    ],
                },
                loginForm: {
                    account:'',
                    password:'',
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
                        if(formName==='registerForm'){
                            const res = await Api.post('/fmms/cgi-bin/hello_world.cgi/member_register', {
                                account:this.registerForm.registerAccount,
                                password:this.registerForm.registerPassword,
                                name:this.registerForm.name,
                                sex:this.registerForm.sex,
                            })
                            if(res.status){
                                global.get('app').$message({
                                    type: 'success',
                                    message: '注册成功'
                                })
                                this.toggle = 'login'
                            }else {
                                global.get('app').$message({
                                    type: 'error',
                                    message: '注册失败，请重试'
                                })
                            }

                        }else {
                            //登录
                            const res = await Api.post('/fmms/cgi-bin/hello_world.cgi/member_login', {
                                account:this.loginForm.account,
                                password:this.loginForm.password,
                            })
                            if(res.status){
                                global.get('app').$message({
                                    type: 'success',
                                    message: '登录成功'
                                })
                            }else{
                                global.get('app').$message({
                                    type: 'error',
                                    message: '账号或密码错误'
                                })
                            }

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