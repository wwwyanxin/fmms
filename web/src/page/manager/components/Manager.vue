<template>
    <div>
        {{manager}}
        <el-tabs v-model="activeName" @tab-click="handleClick">
            <el-tab-pane lazy label="会员信息管理" name="contentLib">
                <Contentlib @switchActive="switchActive"></Contentlib>
            </el-tab-pane>
            <el-tab-pane lazy label="媒体管理" name="mediaLib">
                <Medialib></Medialib>
            </el-tab-pane>
            <el-tab-pane lazy label="推荐卡片管理" name="cardLib">
                <Clusterlib></Clusterlib>
            </el-tab-pane>
            <el-tab-pane lazy label="标签库管理" name="tagLib">
                <Taglib></Taglib>
            </el-tab-pane>
            <el-tab-pane lazy label="客户端预览" name="previewLib">
                <Previewlib></Previewlib>
            </el-tab-pane>
            <el-tab-pane lazy label="其他工具" name="toolsLib">其他工具1222</el-tab-pane>
        </el-tabs>
    </div>
</template>

<script>
    import {cloneDeep, getUrl} from '@/lib/util'
    import Api from '@/service/api.js'
    import global from '@/service/global'

    export default {
        name: "Home",
        data() {
            return {
                manager: "",
                activeName: 'contentLib'
            }
        },
        created() {
        },
        beforeDestroy() {
        },
        async mounted() {
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
            // 切换模块
            switchActive(name) {
                if (name) {
                    this.activeName = name
                }
            },
            handleClick(tab, event) {
                console.log(this.activeName)
            },
        },
        computed: {}
    }
</script>

<style scoped>

</style>
