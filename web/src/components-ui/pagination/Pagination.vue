<template>
    <el-pagination
            background
            layout="total,jumper,prev, pager, next"
            @current-change="pageChange"
            :current-page="info.pageIndex"
            :page-size="info.pageSize"
            :total="info.total"
            style="display: inline-block;position: absolute;right:0;"
    >
    </el-pagination>
</template>

<script>
    export default {
        name: "Pagination",
        props:{
            info:{}
        },
        methods: {
            pageChange(index) {
                this.$emit('change',index)
            },
        },
    }
</script>

<style scoped>

</style>
