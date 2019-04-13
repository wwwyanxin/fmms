<template>
    <div>
        <div class="add">
            <el-button type="warning" size="mini" @click="handleAdd()">添加场馆</el-button>
        </div>
        <div class="table">
            <el-table
                    :data="venueList"
                    height="600"
                    border
                    stripe
                    style="width: 100%">
                <el-table-column
                        prop="id"
                        label="ID"
                        width="80">
                </el-table-column>
                <el-table-column
                        prop="name"
                        label="场馆名称"
                >
                </el-table-column>
                <el-table-column
                        prop="capacity"
                        label="容纳人数"
                >
                </el-table-column>

                <el-table-column
                        prop="status"
                        label="容纳人数"
                >
                    <template slot-scope="scope">
                        {{scope.row.status === 'on' ? '正常':'停用'}}
                    </template>
                </el-table-column>

                <el-table-column
                        prop="venue_type.type"
                        label="场馆类型"
                >
                </el-table-column>

                <el-table-column label="操作" width="75">
                    <template slot-scope="scope">
                        <el-button
                                size="mini"
                                type="danger"
                                @click="handleEdit(scope.$index, scope.row)">编辑
                        </el-button>
                    </template>
                </el-table-column>
            </el-table>
        </div>

        <div class="edit">
            <el-dialog title="编辑场馆" :visible.sync="dialogVisible" width="55%">
                <el-form>
                    <el-form-item label="场馆名">
                        <el-input v-model="form.name" clearable
                                  style="max-width:300px;"></el-input>
                    </el-form-item>

                    <el-form-item label="容纳人数">
                        <el-input-number v-model="form.capacity" :min="1" label="描述文字">
                        </el-input-number>
                    </el-form-item>

                    <el-form-item label="状态">
                        <el-radio-group v-model="form.status" size="small">
                            <el-radio-button :label="'on'">正常</el-radio-button>
                            <el-radio-button :label="'off'">停用</el-radio-button>
                        </el-radio-group>
                    </el-form-item>

                    <el-form-item label="场馆类型">
                        <el-select v-model="form.venue_type.id" placeholder="请选择">
                            <el-option
                                    v-for="item in typeList"
                                    :key="item.id"
                                    :label="item.type"
                                    :value="item.id">
                            </el-option>
                        </el-select>
                    </el-form-item>
                </el-form>

                <div slot="footer" class="dialog-footer">
                    <el-button @click="dialogVisible = false">取 消</el-button>
                    <el-button type="primary" @click="formConfirm">确 定</el-button>
                </div>

            </el-dialog>

        </div>
    </div>
</template>

<script>
    import Api from '@/service/api.js'
    import {cloneDeep} from '@/lib/util'
    import global from '@/service/global'
    import dayjs from 'dayjs'

    export default {
        name: "VenueModule",
        data(){
            return {
                dialogVisible:false,
                model: '',  // add,update
                venueList:[],
                typeList:[],
                form:{
                    id:"",
                    name:"",
                    venue_type:{}
                }
            }
        },
        mounted(){
            this.pullVenueList();
            this.pullTypeList();
        },
        methods:{
            async pullVenueList(){
                const res = await Api.get("venue_list");
                this.venueList = res.data.venueList;
            },
            async pullTypeList(){
                const res = await Api.get("venue_type_list");
                this.typeList = res.data.typeList;
            },
            dateFormat(dateTime){
                return dayjs(dateTime * 1000).format('YYYY年MM月DD日')
            },
            handleEdit(index, row) {
                this.form = cloneDeep(this.venueList[index])
                this.model = 'update';
                this.dialogVisible = true
            },
            handleAdd() {
                this.form = {
                    status: 'on',
                    venue_type: {},
                };
                this.model = 'add';
                this.dialogVisible = true;
            },
            checkItem(form, field, errorMessage) {
                if (!form[field]) {
                    global.get('app').$message({
                        type: 'error',
                        message: errorMessage
                    })
                    return false;
                } else {
                    return true;
                }
            },
            checkForm() {
                if (this.checkItem(this.form, 'name', '未填写姓名')&&
                        this.checkItem(this.form,'capacity','请填写容纳人数')&&
                        this.checkItem(this.form,'status','请选择场馆状态')&&
                        this.checkItem(this.form.venue_type,'id','请选择场馆类型')
                ) {
                    return true;
                } else {
                    return false;
                }
            },
            async formConfirm(){
                if (!this.checkForm()) {
                    return
                }
                await Api.post(`venue_${this.model}`,this.form);
                this.pullVenueList();
                this.dialogVisible = false;
            }
        },
    }
</script>

<style scoped>

</style>