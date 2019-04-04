<template>
    <el-table
            border
            :data="topics"
            style="width: 100%;">
        <el-table-column
                prop="id"
                label="topicId"
                width="100"
        ></el-table-column>
        <el-table-column
                prop="sourcename"
                label="名称"
                width="300"
        ></el-table-column>
        <el-table-column label="状态">
            <template slot-scope="scope">
                <el-tag v-if="judgeStatus(scope.row) === 'none'" type="info" disable-transitions >
                    无筛选
                </el-tag>
                <el-tag v-else-if="judgeStatus(scope.row) === 'outOf'" type="danger" disable-transitions >
                    全部下架
                </el-tag>
                <el-tag v-else-if="judgeStatus(scope.row) === 'bindTag'" type="success" disable-transitions >
                    全部通过并关联标签
                </el-tag>
                <el-tag v-else-if="judgeStatus(scope.row) === 'custom'" type="primary" disable-transitions >
                    自定义规则
                </el-tag>
            </template>
        </el-table-column>
        <el-table-column
                prop="sourceid"
                label="sourceId"
                width="200"
        ></el-table-column>
        <el-table-column
                prop="articlecount"
                label="articleCount"
                width="130"
        ></el-table-column>
        <el-table-column
                prop="sourcetype"
                label="sourceType"
                width="130"
        ></el-table-column>
        <el-table-column label="操作" width="150">
            <template slot-scope="scope">
                <el-button
                        size="mini"
                        @click="handleEdit(scope.$index, scope.row)">编辑
                </el-button>
                <el-button
                        size="mini"
                        type="danger"
                        @click="handleLog(scope.$index, scope.row)">日志
                </el-button>
            </template>
        </el-table-column>
    </el-table>
</template>

<script>
    export default {
        name: "MediaTable",
        props: {
            topics: {
                type:Array
            },
            XMBookBWInfoList: {},
            XMBookBWInfoFlag: {}
        },
       data() {
            return {
                bwinfoMap: {},
            }
        },
        created() {
            this.bwinfoMap = this.list2Map(this.XMBookBWInfoList.bwinfos,'topicid')
        },
        watch: {
            XMBookBWInfoList: {
                deep: true,
                handler: function () {
                    this.bwinfoMap = this.list2Map(this.XMBookBWInfoList.bwinfos,'topicid')
                }
            }
        },
        methods: {
            handleLog(index, row) {
                console.log(row)
            },
            handleEdit(index, row) {
                this.$parent.updateEditBox(index,row)
            },
            judgeStatus(topics) {
                const bwinfo = this.bwinfoMap.get(topics.id)
                // 判断筛选方式
                if (!bwinfo || !bwinfo.wblist || bwinfo.wblist.length < 1) {
                    return 'none'
                } else if (bwinfo.wblist.length === 1 && (!bwinfo.wblist[0].condtions || bwinfo.wblist[0].condtions.length < 1)) {
                    return bwinfo.wblist[0].flag === this.XMBookBWInfoFlag.kXMBookBWInfoFlagIsBlack? 'outOf':'bindTag'
                } else {
                    return 'custom'
                }
            },
            list2Map(list, key = 'id', key2) {
                let map = new Map()
                for (let item of list) {
                    if (key2) {
                        map.set(item[key][key2], item);
                    } else {
                        map.set(item[key], item);
                    }
                }
                return map
            },
        }
    }
</script>

<style>

</style>
