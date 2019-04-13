<template>
    <div>
        <div class="container">
            <div class="topbar">
                <el-date-picker
                        v-model="tableDate"
                        type="week"
                        format="yyyy 第 WW 周"
                        :picker-options="{firstDayOfWeek:1}"
                        @change="switchDate"
                        placeholder="选择周">
                </el-date-picker>
                <span class="add" v-show="addButton" style="float:right">
                    <el-button type="warning" @click="handleAdd()">安排本周课程</el-button>
                </span>
            </div>

            <!--<el-time-select
                    v-model="start_hour"
                    :picker-options="{
                         start: '10:00',
                         step: '01:00',
                         end: '18:00'
                        }"
                    placeholder="选择时间">
            </el-time-select>-->

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
                            prop="venue.venue_type.type"
                            label="课程类型"
                    >
                    </el-table-column>
                    <el-table-column
                            prop="capacity"
                            label="容纳人数"
                    >
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
        name: "Course",
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
                start_hour: '',
                addButton: false,
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
                if(res.data){
                    this.courseList = res.data.courseList
                    this.addButton = false
                }else {
                    this.courseList = [/*{
                        venue: {
                            venue_type: {},
                        },
                        coach: {},
                    }*/]
                    this.addButton = true
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
        }
    }
</script>

<style scoped>

</style>