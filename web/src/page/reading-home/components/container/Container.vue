<template>
    <div>
            <!--<span>邮箱内容阅读管理系统</span>-->
            <Navigation class="read-nav"></Navigation>
    </div>
    <!--<el-container>
        <el-header>
            <Navigation></Navigation>
             <router-view></router-view>
        </el-header>
    </el-container>-->
</template>

<script>
    import Navigation from "../navigation/Navigation";
    import '../../style/css/index.css'
    export default {
        name: "Container",
        components: {Navigation},
    }
</script>

<style scoped>

</style>

