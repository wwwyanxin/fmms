<template>
    <div>
        <div class="card">
            <el-card class="box-card">
                <div slot="header" class="clearfix">
                    <span>我的信息</span>
                    <el-button @click="handleRenew()" style="float: right; padding: 3px 0" type="text">会员续费</el-button>
                </div>
                <div class="text item">
                    <span class="text-value">账号：{{member.account}}</span>
                    <span class="text-value">ID：{{member.id}}</span>
                </div>
                <div class="text item">
                    <span class="text-value">性别：{{member.sex}}</span>
                    <span class="text-value">姓名：{{member.name}}</span>
                </div>
                <div class="text item">
                    <span class="text-value">注册日期：{{dateFormat(member.start_date)}}</span>
                </div>
                <div class="text item">
                    <span class="text-value">会员到期时间：{{member.end_date === -1 ?"未缴费":dateFormat(member.end_date)}}</span>
                </div>
            </el-card>
        </div>
        <div>
            <el-dialog title="续费" :visible.sync="dialogVisible" width="55%">
                <el-select v-model="renewTime" placeholder="请选择续费时长">
                    <el-option :label="'1个月'" :value="1*30*24*60*60"> </el-option>
                    <el-option :label="'2个月'" :value="2*30*24*60*60"> </el-option>
                    <el-option :label="'3个月'" :value="3*30*24*60*60"> </el-option>
                    <el-option :label="'一个季度（4个月）'" :value="4*30*24*60*60"> </el-option>
                    <el-option :label="'半年（6个月）'" :value="6*30*24*60*60"> </el-option>
                    <el-option :label="'一年（12个月）'" :value="12*30*24*60*60"> </el-option>
                </el-select>
                <div slot="footer" class="dialog-footer">
                    <el-button @click="dialogVisible = false">取 消</el-button>
                    <el-button type="primary" @click="confirm">确 定</el-button>
                </div>
            </el-dialog>
        </div>
    </div>
</template>

<script>
    import global from '@/service/global'
    import dayjs from 'dayjs'
    import Api from '@/service/api.js'

    export default {
        name: "InfoModule",
        data(){
            return {
                member:{},
                renewTime:1*30*24*60*60, //一个月
                dialogVisible: false,
            }
        },
        mounted(){

           /* // 测试默认登录账号
            global.set("member", {
                "account": "wyx",
                "end_date": -1,
                "id": 14,
                "name": "wang",
                "password": "123",
                "sex": "male",
                "start_date": -1
            })*/
            this.member = global.get("member")
        },
        methods:{
            handleRenew(){
                this.dialogVisible = true;
            },
            dateFormat(dateTime){
                return dayjs(dateTime * 1000).format('YYYY年MM月DD日')
            },
            async confirm() {
                let nowTime = parseInt(new Date().getTime()/1000);
                // 已经过期
                if(nowTime > this.member.end_date){
                    this.member.end_date = nowTime + this.renewTime;
                }else{
                    this.member.end_date = this.member.end_date + this.renewTime
                }
                await Api.post(`member_update`, this.member);
                global.get('app').$message({
                                    type: 'success',
                                    message: '续费成功'
                                })
                this.dialogVisible = false
            },
        }
    }
</script>

<style scoped>
    .text {
        font-size: 14px;
    }

    .item {
        margin-bottom: 18px;
    }

    .clearfix:before,
    .clearfix:after {
        display: table;
        content: "";
    }
    .clearfix:after {
        clear: both
    }

    .box-card {
        width: 480px;
    }

    .text-value{
        padding:40px 80px 40px 40px
    }
</style>