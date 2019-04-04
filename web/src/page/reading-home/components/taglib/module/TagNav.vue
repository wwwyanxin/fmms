<template>
    <el-tabs tab-position="left" type="border-card" v-model="activeTag" @tab-click="handleClick">
        <el-tab-pane lazy label="一级标签" name="tag1">
            <Tag1></Tag1>
        </el-tab-pane>
        <el-tab-pane lazy label="二级标签" name="tag2">
            <Tag2></Tag2>
        </el-tab-pane>
    </el-tabs>
</template>

<script>
    import Tag1 from "./Tag1/Tag1";
    import Tag2 from "./Tag2/Tag2";
    export default {
        name: "TagNav",
        components: {Tag1,Tag2},
        data() {
            return {
                activeTag: 'tag1'
            };
        },
        methods: {
            handleClick(tab, event) {
                console.log(tab, event);
            }
        }
    }
</script>

<style scoped>
</style>
