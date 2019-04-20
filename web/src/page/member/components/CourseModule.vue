<template>

    <div>
        <div class="container">
            <div class="topbar">
                <el-date-picker
                        v-model="tableDate"
                        type="week"
                        format="yyyy 第 WW 周"
                        @change="switchDate"
                        :picker-options="pickerOptions"
                        placeholder="选择周">
                </el-date-picker>
            </div>

            <div class="table">
                <el-table
                        :data="courseList"
                        height="500"
                        border
                        stripe
                        empty-text="未安排任何课程"
                        style="width: 100%">
                    <el-table-column
                            prop="id"
                            label="ID"
                            width="80">
                    </el-table-column>
                    <el-table-column
                            prop="start_hour"
                            label="上课时间"
                    >
                    </el-table-column>
                    <el-table-column
                            prop="venue.name"
                            label="场馆"
                    >
                    </el-table-column>
                    <el-table-column
                            prop="coach.name"
                            label="教练"
                            width="80"
                    >
                    </el-table-column>
                    <el-table-column
                            prop="type"
                            label="课程类型"
                    >
                        <template slot-scope="scope">
                            <span>{{ scope.row.type ? scope.row.type : scope.row.venue.venue_type.type }}</span>
                        </template>
                    </el-table-column>
                    <el-table-column
                            prop="capacity"
                            label="容纳人数"
                    >
                    </el-table-column>

                    <el-table-column
                            prop="registration_num"
                            label="已选择人数"
                    >
                    </el-table-column>

                    <el-table-column label="操作" width="75">
                        <template slot-scope="scope">
                            <el-button :disabled="scope.row.capacity<=scope.row.registration_num" type="danger" size="mini" @click="handleBuy(scope.$index, scope.row)">购买</el-button>
                        </template>
                    </el-table-column>

                </el-table>

            </div>
        </div>
    </div>
</template>

<script>
    import Api from '@/service/api.js'
    import {cloneDeep} from '@/lib/util'
    import global from '@/service/global'
    import dayjs from 'dayjs'

    export default {
        name: "CourseModule",
        data() {
            return {
                courseList: [
                    {
                        "id": '',
                        "start_date": '',
                        "start_hour": '',
                        "capacity": '',
                        "type": "",
                        "price": '',
                        "coach": {
                            "entry_date": '',
                            "id": '',
                            "introduction": '',
                            "name": "",
                            "sex": "",
                            "status": ""
                        },
                        "venue": {
                            "capacity": '',
                            "id": '',
                            "name": "",
                            "status": "",
                            "venue_type": {
                                "id": '',
                                "type": ""
                            }
                        }
                    }
                ],
                tableDate: new Date(),
                start_date: this.dateFormat(this.getFirstDay(new Date())),
                dialogVisible: false,
                pickerOptions: {
                    firstDayOfWeek:1,
                    disabledDate(time) {
                        return time.getTime() < (Date.now()-1*24*60*60*1000);
                    },
                }
            }
        },
        mounted() {
            this.pullCourseList();
        },
        methods: {
            async pullCourseList() {
                const res = await Api.get('course_get_week', {
                    start_date: this.start_date,
                })
                if (res.data) {
                    this.courseList = res.data.courseList
                } else {
                    this.courseList = []
                }
            },
            getFirstDay(date) {
                let day = date.getDay() || 7;
                return new Date(date.getFullYear(), date.getMonth(), date.getDate() + 1 - day);
            },
            dateFormat(date) {
                return date.getTime() / 1000
            },
            switchDate() {
                if (!this.tableDate) {
                    return
                }
                this.start_date = this.dateFormat(this.getFirstDay(this.tableDate))
                this.pullCourseList()
            },


            handleBuy(index, row) {
                this.$confirm(`此操作将花费${row.price}元, 是否继续?`, '提示', {
                    confirmButtonText: '确定',
                    cancelButtonText: '取消',
                    type: 'warning'
                }).then(() => {
                    row.registration_num++;
                    this.formConfirm(row)
                    this.$message({
                        type: 'success',
                        message: '购买成功!'
                    });
                }).catch(() => {
                    this.$message({
                        type: 'info',
                        message: '已取消购买'
                    });
                });
            },

            async formConfirm(course) {
                await Api.post("course_buy", {
                        course: JSON.stringify(course),
                        member_id:global.get("member").id,
                    }
                );
                //this.pullCourseList();
                this.dialogVisible = false;
            }
        }
    }
</script>

<style scoped>

</style>