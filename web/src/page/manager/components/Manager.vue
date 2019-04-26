<template>
    <div>
        <div style="position: fixed;right: 20px;top:3px;z-index: 1;">
            <el-button type="success" plain >{{manager.account}}</el-button>
            <el-button type="danger" size="mini" round @click="logout">退出</el-button>
        </div>
        <el-tabs v-model="activeName" type="card">
            <el-tab-pane lazy label="会员信息管理" name="MemberModule">
                <MemberModule v-if="activeName === 'MemberModule'"></MemberModule>
            </el-tab-pane>
            <el-tab-pane lazy label="教练管理" name="CoachModule">
                <CoachModule v-if="activeName === 'CoachModule'"></CoachModule>
            </el-tab-pane>
            <el-tab-pane lazy label="场馆管理" name="VenueModule">
                <VenueModule v-if="activeName === 'VenueModule'"></VenueModule>
            </el-tab-pane>
            <el-tab-pane lazy label="课程管理" name="CourseModule">
                <CourseModule v-if="activeName === 'CourseModule'"></CourseModule>
            </el-tab-pane>
            <el-tab-pane lazy label="续费订单查看" name="RenewOrder">
                <RenewOrder v-if="activeName === 'RenewOrder'" :listParam="{ type: 'all', param: '', }" ></RenewOrder>
            </el-tab-pane>
            <el-tab-pane lazy label="课程订单查看" name="CourseOrder">
                <CourseOrder v-if="activeName === 'CourseOrder'" :list-param="{ type: 'all', param: '', }"></CourseOrder>
            </el-tab-pane>
        </el-tabs>
    </div>
</template>

<script>
    import {cloneDeep, getUrl} from '@/lib/util'
    import Api from '@/service/api.js'
    import global from '@/service/global'
    import MemberModule from "./MemberModule";
    import CoachModule from "./CoachModule";
    import VenueModule from "./VenueModule";
    import CourseModule from "./CourseModule";
    import RenewOrder from "../../../components-ui/order/RenewOrder";
    import CourseOrder from "../../../components-ui/order/CourseOrder";

    export default {
        name: "Home",
        components: {CourseOrder, RenewOrder, CourseModule, VenueModule, CoachModule, MemberModule},
        data() {
            return {
                manager: "",
                activeName: 'MemberModule'
            }
        },
        created() {},
        beforeDestroy() {},
        async mounted() {
            /*// 测试默认登录账号
            global.set("manager",{
                account:'wyx',
                id:'1'
            })*/

            if (global.get("manager")) {
                this.manager = global.get("manager");
            } else {
                global.get('app').$message({
                    type: 'error',
                    message: '请先登录'
                })
                this.$router.push("/login");
            }
        },
        methods: {
            logout(){
                global.set("manager",false);
                this.$router.push("/login");
            }
        },
        computed: {}
    }
</script>

<style scoped>

</style>
