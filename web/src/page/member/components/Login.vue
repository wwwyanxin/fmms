<template>
    <div style="text-align: center;">
        <el-card shadow="hover" style="width:500px;margin-top:30px;display:inline-block">
            <div class="container" style="margin-right: 35px;">
                <div class="register">
                    <el-form :model="ruleForm2" size="mini" status-icon :rules="rules2" ref="ruleForm2" label-width="100px"
                             class="demo-ruleForm">
                        <el-form-item label="账号" prop="account">
                            <el-input type="text" v-model="ruleForm2.account" autocomplete="off"></el-input>
                        </el-form-item>

                        <el-form-item label="密码" prop="password">
                            <el-input type="password" v-model="ruleForm2.password" autocomplete="off"></el-input>
                        </el-form-item>
                        <el-form-item label="确认密码" prop="checkPass">
                            <el-input type="password" v-model="ruleForm2.checkPass" autocomplete="off"></el-input>
                        </el-form-item>
                        <el-form-item label="姓名" prop="name">
                            <el-input type="text" v-model="ruleForm2.name" autocomplete="off"></el-input>
                        </el-form-item>
                        <el-form-item label="性别" prop="sex">
                            <el-input type="text" v-model="ruleForm2.sex" autocomplete="off"></el-input>
                        </el-form-item>
                        <!--<el-form-item label="年龄" prop="age" autocomplete="off">
                            <el-input v-model.number="ruleForm2.age"></el-input>
                        </el-form-item>-->
                        <el-form-item>
                            <el-button type="primary" @click="submitForm('ruleForm2')">提交</el-button>
                            <el-button @click="resetForm('ruleForm2')">重置</el-button>
                        </el-form-item>
                    </el-form>
                </div>
                <div class="login">

                </div>
            </div>
        </el-card>
    </div>
</template>

<script>
    export default {
        name: "Login",
        data() {
            var validatePass = (rule, value, callback) => {
                if (value === '') {
                    callback(new Error('请输入密码'));
                } else {
                    if (this.ruleForm2.checkPass !== '') {
                        this.$refs.ruleForm2.validateField('checkPass');
                    }
                    callback();
                }
            };
            var validatePass2 = (rule, value, callback) => {
                if (value === '') {
                    callback(new Error('请再次输入密码'));
                } else if (value !== this.ruleForm2.password) {
                    callback(new Error('两次输入密码不一致!'));
                } else {
                    callback();
                }
            };
            var validateAccount = (rule,value,callback) => {
                if (!value) {
                    return callback(new Error('账号不能为空'));
                }
                setTimeout(() => {
                    callback();
                }, 1000);
            };
            var validateName = (rule,value,callback) => {
                if (!value) {
                    return callback(new Error('姓名不能为空'));
                }
                callback();
            };
            var validateSex = (rule,value,callback) => {
                if (!value) {
                    return callback(new Error('性别不能为空'));
                }
                callback();
            };
            return {
                ruleForm2: {
                    age: '',
                    account:'',
                    password:'',
                    checkPass: '',
                    name:'',
                    sex:''

                },
                rules2: {
                    pass: [
                        {validator: validatePass, trigger: 'blur'}
                    ],
                    checkPass: [
                        {validator: validatePass2, trigger: 'blur'}
                    ],
                    account: [
                        {validator: validateAccount, trigger: 'blur'}
                    ],
                    password: [
                        {validator: validatePass, trigger: 'blur'}
                    ],
                    name: [
                        {validator: validateName, trigger: 'blur'}
                    ],
                    sex: [
                        {validator: validateSex, trigger: 'blur'}
                    ],
                }
            };
        },
        methods: {
            submitForm(formName) {
                this.$refs[formName].validate((valid) => {
                    if (valid) {
                        alert('submit!');
                    } else {
                        console.log('error submit!!');
                        return false;
                    }
                });
            },
            resetForm(formName) {
                this.$refs[formName].resetFields();
            }
        }
    }
</script>

<style scoped>

</style>