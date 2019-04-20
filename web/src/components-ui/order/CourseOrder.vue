<template>
    <div>
        <div class="table">
            <el-table
                    :data="courseOrderList"
                    border
                    stripe
                    empty-text="无订单"
                    style="width: 100%">
                <el-table-column
                        prop="id"
                        label="ID"
                        width="40">
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
                        width="80"
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
                        prop="course.id"
                        label="课程ID"
                        width="70"
                >
                </el-table-column>

                <el-table-column
                        prop="course.start_date"
                        label="课程开始日期（一周）"
                >
                    <template slot-scope="scope">
                        <i class="el-icon-time"></i>
                        {{scope.row.course?dateFormat(scope.row.course.start_date):''}}
                    </template>
                </el-table-column>

                <el-table-column
                        prop="course.start_hour"
                        label="课程开始时间"
                >
                </el-table-column>

                <el-table-column
                        prop="course.venue.name"
                        label="场馆"
                >
                </el-table-column>
                <el-table-column
                        prop="course.coach.name"
                        label="教练"
                        width="70"
                >
                </el-table-column>
                <el-table-column
                        prop="course.type"
                        label="课程类型"
                >
                    <template slot-scope="scope">
                        <span>{{ scope.row.course.type ? scope.row.course.type : scope.row.course.venue.venue_type.type }}</span>
                    </template>
                </el-table-column>
                <el-table-column
                        prop="course.capacity"
                        label="课程容纳人数"
                >
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
        name: "CourseOrder",
        props: {
            listParam: {
                type:Object
            }
        },
        data() {
            return {
                courseOrderList: [],
            }
        },
        mounted() {
            this.pullCourseOrderList();
        },
        methods: {
            dateFormat(dateTime) {
                return dayjs(dateTime * 1000).format('YYYY年MM月DD日')
            },
            async pullCourseOrderList() {
                let res;
                if (this.listParam.type === 'all') {
                    res = await Api.get("course_order_list");
                } else if (this.listParam.type === 'member') {
                    res = await Api.get("course_order_list", {
                        member_id: this.listParam.param
                    })
                } else if (this.listParam.type === 'course') {
                    res = await Api.get("course_order_list", {
                        course_id: this.listParam.param
                    })
                }
                if(res.data){
                    this.courseOrderList = res.data.courseOrderList ;
                }else{
                    this.courseOrderList = []
                }
            },

        },

    }
</script>

<style scoped>

</style>