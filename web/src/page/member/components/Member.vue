<template>
    <div>
        <div style="position: fixed;right: 20px;top:3px;">
            <el-button type="danger" plain>{{member.account}}</el-button>
        </div>
        <el-tabs v-model="activeName" type="card">
            <el-tab-pane lazy label="个人信息" name="InfoModule">
                <InfoModule v-if="activeName === 'InfoModule'"></InfoModule>
            </el-tab-pane>

            <el-tab-pane lazy label="购买课程" name="CourseModule">
                <CourseModule v-if="activeName === 'CourseModule'"></CourseModule>
            </el-tab-pane>

            <el-tab-pane lazy label="我的订单" name="Order">
                <div v-if="activeName === 'Order'">
                    <el-tag>续费订单</el-tag>
                    <RenewOrder :listParam="listParam" ></RenewOrder>

                    <el-tag type="success">课程订单</el-tag>
                    <CourseOrder :list-param="listParam"></CourseOrder>
                </div>
            </el-tab-pane>

        </el-tabs>
    </div>
</template>

<script>
    import {cloneDeep, getUrl} from '@/lib/util'
    import Api from '@/service/api.js'
    import global from '@/service/global'
    import InfoModule from "./InfoModule";
    import RenewOrder from "../../../components-ui/order/RenewOrder";
    import CourseModule from "./CourseModule";
    import CourseOrder from "../../../components-ui/order/CourseOrder";

    export default {
        name: "Member",
        components: {CourseOrder, CourseModule, RenewOrder, InfoModule},
        data() {
            return {
                member: {},
                activeName: "InfoModule",
                listParam:{}
            }
        },
        created() {
        },
        beforeDestroy() {
        },
        async mounted() {

            if (global.get("member")) {
                this.member = global.get("member");

                this.listParam = {
                    type: 'member',
                    param: this.member.id,
                }
            } else {
                global.get('app').$message({
                    type: 'error',
                    message: '请先登录'
                })
                this.$router.push("/login");
            }

        },
        methods: {},
        computed: {}
    }
</script>

<style scoped>


</style>
