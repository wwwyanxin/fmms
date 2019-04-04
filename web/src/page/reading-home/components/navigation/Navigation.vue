<template>
    <div>
        <div style="position: fixed;right: 20px;top:3px;">
            <el-button type="danger" round @click="logout">退出</el-button>
        </div>
        <el-tabs v-model="activeName" @tab-click="handleClick">
            <el-tab-pane lazy label="内容列表" name="contentLib">
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
    import Taglib from "../taglib/Taglib";
    import Contentlib from "../contentlib/Contentlib"
    import Clusterlib from "../clusterlib/Clusterlib";
    import Medialib from "../medialib/Medialib";
    import Previewlib from "../previewlib/Previewlib";

    export default {
        name: "Navigation",
        components: {Previewlib, Medialib, Clusterlib, Taglib, Contentlib},
        data() {
            return {
                activeName: 'contentLib'
            };
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
            /**
             * 智能网关统一登出
             */
            logout() {
                window.location.href = '/_logout/?url=http%3a%2f%2fxmail.oa.com%2foa%2fcall%3ffunc%3d4%26t%3dread-home'
            },
        }
    }
</script>

<style scoped>

</style>
