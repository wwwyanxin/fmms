<template>
    <el-table
            border
            :data="fatherlist"
            :row-class-name="specialClass"
    >
        <el-table-column
                prop="father.name"
                label="标签名称"
                :width="tagLevel === 1 ? '180' : ''"
        >
        </el-table-column>
        <el-table-column
                v-if="tagLevel === 1"
                align="center"
                prop="connectContentTag"
                label="关联二级标签"
                >
            <template slot-scope="scope">
                <el-tag style="margin-right:10px" disable-transitions type="success" v-for="(item,index) in scope.row.childlist">{{ item.name }}</el-tag>
            </template>
        </el-table-column>
        <el-table-column label="操作" width="150">
            <template slot-scope="scope">
                <el-button
                        :disabled="specialTag(scope.row)"
                        size="mini"
                        @click="handleEdit(scope.$index, scope.row)">编辑</el-button>
                <el-button
                        :disabled="specialTag(scope.row)"
                        size="mini"
                        type="danger"
                        @click="handleDelete(scope.$index, scope.row)">删除</el-button>
            </template>
        </el-table-column>
    </el-table>
</template>

<script>
    export default {
        name: "TabTable",
        props:{
            fatherlist: {
                type: Array
            },
            tagLevel: {
                type:Number
            }
        },
        methods: {
            handleEdit(index, row) {
                this.$parent.updateTagBox(index,row)
            },
            handleDelete(index, row) {
                this.$confirm('这个操作将会删除此标签，请确保没有其他标签，或卡片关联此标签!!!', '提示', {
                    confirmButtonText: '确定',
                    cancelButtonText: '取消',
                    type: 'warning'
                }).then(() => {
                    this.$parent.deleteTag({id:row.father.id})
                    this.$message({
                        type: 'success',
                        message: '正在删除...'
                    });
                }).catch(() => {
                    this.$message({
                        type: 'info',
                        message: '已取消操作'
                    });
                });
            },
            // banner标签为特殊标签, 前后端都特殊处理
            specialTag(row) {
                if (row.father.name === 'banner' && this.tagLevel === 1) {
                    return true;
                } else {
                    return false
                }
            },
            // 特殊标签的高亮
            specialClass(scope) {
                if (this.specialTag(scope.row)) {
                    return 'success-row';
                } else {
                    return ''
                }
            }
        }
    }
</script>

<style>

</style>
