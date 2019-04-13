<template>
    <div>
        <div style="position: fixed;right: 20px;top:3px;">
            <el-button type="danger" plain >{{manager.account}}</el-button>
        </div>
        <el-tabs v-model="activeName" type="card">
            <el-tab-pane lazy label="会员信息管理" name="MemberModule">
                <MemberModule></MemberModule>
            </el-tab-pane>
            <el-tab-pane lazy label="教练管理" name="CoachModule">
                <CoachModule></CoachModule>
            </el-tab-pane>
            <el-tab-pane lazy label="场馆管理" name="VenueModule">
                <VenueModule></VenueModule>
            </el-tab-pane>
            <el-tab-pane lazy label="课程管理" name="CourseModule">
                <CourseModule></CourseModule>
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

    export default {
        name: "Home",
        components: {CourseModule, VenueModule, CoachModule, MemberModule},
        data() {
            return {
                manager: "",
                activeName: 'CourseModule'
            }
        },
        created() {},
        beforeDestroy() {},
        async mounted() {
            // 测试默认登录账号
            global.set("manager",{
                account:'wyx',
                id:'1'
            })

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
        /*    // 切换模块
            switchActive(name) {
                if (name) {
                    this.activeName = name
                }
            },
            handleClick(tab, event) {
                console.log(this.activeName)
            },*/
        },
        computed: {}
    }
</script>

<style scoped>

</style>
