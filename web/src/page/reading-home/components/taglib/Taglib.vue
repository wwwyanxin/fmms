<template>
    <div>
        <!--<Topbar></Topbar>-->
        <TagNav style="margin-top:20px;"></TagNav>
        <!--<TagTable :tableData="tableInfo"></TagTable>-->
        <!--<EditTag ref="editTag" :info="editInfo"></EditTag>-->
    </div>
</template>

<script>
/*    import Topbar from "./module/Topbar";
    import TagTable from "./module/TagTable";
    import EditTag from "./module/EditTag"*/
    import TagNav from "./module/TagNav";

    export default {
        name: "Taglib",
        components: {TagNav},
    }
</script>

<style scoped>

</style>
