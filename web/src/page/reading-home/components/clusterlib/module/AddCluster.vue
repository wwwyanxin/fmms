<template>
    <el-dialog title="新增卡片" :visible.sync="dialogVisible" width="55%">
        <el-form>
            <el-form-item label="卡片名">
                <el-input v-model="clusterName" auto-complete="off" clearable
                          style="max-width:300px;"></el-input>
            </el-form-item>
        </el-form>
        <div slot="footer" class="dialog-footer">
            <el-button @click="dialogVisible = false">取 消</el-button>
            <el-button type="primary" @click="confirm">确 定</el-button>
        </div>
    </el-dialog>
</template>

<script>
    export default {
        name: "AddCluster",
        props: {},
        data() {
            return {
                dialogVisible: false,
                clusterName: ''
            }
        },
        methods: {
            show() {
                this.dialogVisible = true;
            },
            confirm() {
                if (!this.checkName()) {
                    return
                }
                this.$bus.$emit('clusterHandler', {
                    func: 'sendAddCluster',
                    args: {
                        func: 5,
                        addclusterinforeq: JSON.stringify({
                            clusterinfo: {
                                name: this.clusterName
                            }
                        })
                    }
                })
                this.dialogVisible = false;
            },
            checkName() {
                if (this.clusterName.length > 5) {
                    this.$message({
                        type: 'error',
                        message: '名称长度不应超过5'
                    });
                    return false
                }else if(this.clusterName.length < 1){
                    this.$message({
                        message: '名称不能为空',
                        type: 'error'
                    })
                    return false
                }
                return true
            },
        }
    }
</script>

<style scoped>

</style>
