<template>
    <div>
        <div style="position: fixed;right: 20px;top:3px;">
            <el-button type="danger" plain>{{member.account}}</el-button>
        </div>
        <el-tabs v-model="activeName" type="card">
            <el-tab-pane lazy label="个人信息" name="InfoModule">
                <InfoModule v-if="activeName === 'InfoModule'"></InfoModule>
            </el-tab-pane>
        </el-tabs>
    </div>
</template>

<script>
    import {cloneDeep, getUrl} from '@/lib/util'
    import Api from '@/service/api.js'
    import global from '@/service/global'
    import InfoModule from "./InfoModule";

    export default {
        name: "Member",
        components: {InfoModule},
        data() {
            return {
                member: {},
                activeName: "InfoModule"
            }
        },
        created() {
        },
        beforeDestroy() {
        },
        async mounted() {

            if (global.get("member")) {
                this.member = global.get("member");
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
