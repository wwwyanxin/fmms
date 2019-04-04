<template>
    <div>
        <el-button type="warning" size="mini" round @click="addTagBox()">新增卡片</el-button>
        <AddCluster ref="addClusterBox"></AddCluster>
    </div>
</template>

<script>
    import AddCluster from './AddCluster'
    export default {
        name: "topbar",
        components: {AddCluster},

        methods:{
            addTagBox(){
                this.$refs.addClusterBox.show()
            }
        }
    }
</script>

<style scoped>

</style>
