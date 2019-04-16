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

                </el-table>

            </div>
            <div class="edit">
                <el-dialog :title="'课程计划'" :visible.sync="dialogVisible" :show-close="false"
                           :close-on-press-escape="false" :close-on-click-modal="false" width="800px" top="5vh">
                    <el-dialog
                            width="30%"
                            title="注意"
                            :visible.sync="innerVisible"
                            append-to-body>
                        <span>确认课程后不能修改</span>
                        <div slot="footer" class="dialog-footer">
                            <el-button @click="innerVisible = false">取 消</el-button>
                            <el-button type="primary" @click="formConfirm">确 定</el-button>
                        </div>
                    </el-dialog>
                    <el-form style="max-height: 350px;overflow-y: auto;" size="mini" v-if="dialogVisible">
                        <div>
                            <el-card v-for="(courseItem,courseIndex) in courseList" class="box-card"
                                     :body-style="{ padding: '5px' }"
                                     style="margin:10px;">
                                <el-form-item :label="`课程:${courseIndex + 1}`">
                                    <div style="display:inline-block;">
                                        <el-time-select
                                                v-model="courseItem.start_hour"
                                                :picker-options="{ start: '10:00', step: '01:00', end: '18:00' }"
                                                size="mini"
                                                @change="hourChange(courseItem)"
                                                class="width_100"
                                                placeholder="时间">
                                        </el-time-select>
                                        <el-select v-model="courseItem.venue.id" placeholder="场馆"
                                                   @change="venueChange(courseItem)" :disabled="!courseItem.start_hour"
                                                   class="width_100">
                                            <el-option
                                                    v-for="venueItem in venueFilter(courseItem.start_hour)"
                                                    :key="venueItem.id"
                                                    :label="venueItem.name"
                                                    :value="venueItem.id">
                                            </el-option>
                                        </el-select>
                                        <el-select v-model="courseItem.coach.id" placeholder="教练"
                                                   @change="coachChange(courseItem)" :disabled="!courseItem.start_hour"
                                                   class="width_100">
                                            <el-option
                                                    v-for="coachItem in coachFilter(courseItem.start_hour)"
                                                    :key="coachItem.id"
                                                    :label="coachItem.name"
                                                    :value="coachItem.id">
                                            </el-option>
                                        </el-select>
                                        <el-input placeholder="课程类型" v-model="courseItem.type"
                                                  :disabled="!isFreeType(courseItem)" class="width_100"></el-input>
                                        <el-input type="number" @change="capacityChange(courseItem)"
                                                  onkeyup="value=value.replace(/^(0+)|[^\d]+/g,'')"
                                                  v-model="courseItem.capacity" :min="1"
                                                  :max="courseItem.venue.capacity"
                                                  :disabled="!courseItem.venue.id"
                                                  style="width:70px"></el-input>
                                        人，
                                        <el-input type="number" step="0.01" v-model="courseItem.price" :min="0"
                                                  @change="priceChange(courseItem)"
                                                  style="width:90px;"></el-input>
                                        元
                                        <i @click="removeCourse(courseIndex)" class="el-icon-remove"
                                           style="float:right;margin: 3px 0px 0px 10px;font-size: 25px;vertical-align: top;cursor: pointer"></i>
                                    </div>

                                </el-form-item>
                            </el-card>
                            <i @click="addCourse"
                               class="el-icon-circle-plus"
                               style="margin: -30px 37px 17px 17px;font-size: 30px;cursor: pointer;"></i>
                        </div>
                    </el-form>
                    <div slot="footer" class="dialog-footer">
                        <el-button @click="dialogVisible = false ; courseList = []">取 消</el-button>
                        <el-button type="primary" @click="outConfirm">确 定</el-button>
                    </div>

                </el-dialog>
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
                venueList: [],
                coachList: [],
                tableDate: new Date(),
                start_date: this.dateFormat(this.getFirstDay(new Date())),
                start_hour: '',
                addButton: false,
                dialogVisible: false,
                innerVisible:false
            }
        },
        mounted() {
            this.pullCoachList();
            this.pullVenueList();
            this.pullCourseList();
        },
        methods: {
            priceChange(courseItem) {
                courseItem.price = parseFloat(courseItem.price);
                courseItem.price = courseItem.price >= 0 ? courseItem.price : 0;
            },
            capacityChange(courseItem) {
                courseItem.capacity = parseInt(courseItem.capacity)
                courseItem.capacity = courseItem.capacity > courseItem.venue.capacity ? courseItem.venue.capacity : courseItem.capacity;
            },
            hourChange(courseItem) {
                courseItem.venue = {
                    venue_type: {type:''},
                };
                courseItem.coach = {};

            },
            venueChange(courseItem) {
                courseItem.venue = cloneDeep(this.venueList.find(item => {
                    return item.id === courseItem.venue.id
                }))
                if (courseItem.venue.venue_type.type === 'free') {
                    courseItem.type = '';
                } else {
                    courseItem.type = cloneDeep(courseItem.venue.venue_type.type);
                }
                courseItem.capacity = courseItem.venue.capacity

            },
            coachChange(courseItem) {
                courseItem.coach = cloneDeep(this.coachList.find(item => {
                    return item.id === courseItem.coach.id
                }))
            },
            venueFilter(start_hour) {
                const _this = this
                let venueList = cloneDeep(this.venueList);
                let res = venueList.filter(venueItem => {
                    let index = _this.courseList.findIndex(courseItem => {
                        return start_hour === courseItem.start_hour && courseItem.venue.id === venueItem.id
                    })
                    return index === -1 && venueItem.status === 'on'
                })
                return res;

            },
            coachFilter(start_hour) {
                const _this = this
                let coachList = cloneDeep(this.coachList);
                let res = coachList.filter(coachItem => {
                    let index = _this.courseList.findIndex(courseItem => {
                        return start_hour === courseItem.start_hour && courseItem.coach.id === coachItem.id
                    })
                    return index === -1 && coachItem.status === 'on_work';
                })
                return res;
            },
            isFreeType(courseItem) {
                return courseItem.venue.id !== undefined && courseItem.venue.venue_type.type === 'free';
            },
            async pullCoachList() {
                const res = await Api.get("coach_list");
                this.coachList = res.data.coachList;
            },
            async pullVenueList() {
                const res = await Api.get("venue_list");
                this.venueList = res.data.venueList;
            },
            async pullCourseList() {
                const res = await Api.get('course_get_week', {
                    start_date: this.start_date,
                })
                if (res.data) {
                    this.courseList = res.data.courseList
                    this.addButton = false
                } else {
                    this.courseList = []
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
                this.courseList = [{
                    start_date: this.start_date,
                    venue: {
                        venue_type: {type:''},
                    },
                    coach: {},
                    price:0,
                }];
                this.dialogVisible = true;
            },
            addCourse() {
                this.courseList.push({
                    start_date: this.start_date,
                    venue: {
                        venue_type: {type:''},
                    },
                    coach: {},
                    price:0,
                })
            },
            removeCourse(courseIndex) {
                this.courseList.splice(courseIndex, 1)
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
                if (this.courseList.length === 0) {
                    return false;
                }
                for (let course of this.courseList) {
                    if (this.checkItem(course, 'start_hour', '请填写时间') &&
                        this.checkItem(course.venue, 'id', '请选择场馆') &&
                        this.checkItem(course.coach, 'id', '请选择教练') &&
                        this.checkItem(course, 'type', '请填写课程类型') &&
                        this.checkItem(course, 'capacity', '请设置写容纳人数')
                    ) {
                        continue;
                    } else {
                        return false;
                    }
                }
                return true;
            },
            outConfirm(){
                if(this.checkForm()){
                    this.innerVisible = true
                }
            },
            async formConfirm() {
                await Api.post("course_add_week", {
                        courseList: JSON.stringify(this.courseList)
                    }
                );
                this.pullCourseList();
                this.innerVisible = false;
                this.dialogVisible = false;
            }
        }
    }
</script>

<style scoped>

    .width_100 {
        width: 100px;
    }
</style>