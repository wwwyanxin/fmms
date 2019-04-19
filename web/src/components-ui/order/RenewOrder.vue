<template>
    <div>
        <div class="table">
            <el-table
                    :data="renewOrderList"
                    border
                    stripe
                    style="width: 100%">
                <el-table-column
                        prop="id"
                        label="ID"
                        width="80">
                </el-table-column>
                <el-table-column
                        prop="price"
                        label="价格"
                >
                </el-table-column>
                <el-table-column
                        prop="time"
                        label="下单时间"
                >
                    <template slot-scope="scope">
                        <i class="el-icon-time"></i>
                        {{dateFormat(scope.row.time)}}
                    </template>
                </el-table-column>

                <el-table-column
                        prop="member.id"
                        label="用户ID"
                        width:"80"
                >
                </el-table-column>

                <el-table-column
                        prop="member.account"
                        label="用户账户号"
                >
                </el-table-column>

                <el-table-column
                        prop="member.name"
                        label="用户姓名"
                >
                </el-table-column>

                 <el-table-column
                        prop="start_date"
                        label="开始时间"
                >
                    <template slot-scope="scope">
                        {{dateFormat(scope.row.start_date)}}
                    </template>
                </el-table-column>

                <el-table-column
                        prop="end_date"
                        label="结束时间"
                >
                    <template slot-scope="scope">
                        {{dateFormat(scope.row.end_date)}}
                    </template>
                </el-table-column>


            </el-table>
        </div>
    </div>
</template>

<script>
    import Api from '@/service/api.js'
    import {cloneDeep} from '@/lib/util'
    import global from '@/service/global'
    import dayjs from 'dayjs'

    export default {
        name: "RenewOrder",
        props: {
            listParam: {
                type:Object
            }
        },
        data() {
            return {
                renewOrderList: [
                    {
                        member:{},
                    }
                ],
            }
        },
        mounted() {
            this.pullRenewOrderList();
        },
        methods: {
            dateFormat(dateTime) {
                return dayjs(dateTime * 1000).format('YYYY年MM月DD日')
            },
            async pullRenewOrderList() {
                let res;
                if (this.listParam.type === 'all') {
                    res = await Api.get("renew_order_list");
                } else if (this.listParam.type === 'member') {
                    res = await Api.get("renew_order_list", {
                        member_id: this.listParam.param
                    })
                }
                this.renewOrderList = res.data.renewOrderList;
            },

        },

    }
</script>

<style scoped>

</style>