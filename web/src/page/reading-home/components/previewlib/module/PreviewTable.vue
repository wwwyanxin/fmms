<template>
    <div>
        <el-table
                :data="allArticle"
                style="width: 100%"
                stripe
                highlight-current-row
                @current-change="handleCurrentChange"
        >
            <el-table-column
                    prop="contentFromInfo"
                    label="内容信息"
                    width="192"
            >
                <template slot-scope="scope">
                    <el-card class="box-card">
                        <div @click='tableClickHandler(scope.row)' style="cursor:pointer">
                            <span v-if="scope.$index === 0">
                                <el-tag disable-transitions size="medium" hit> banner卡片 </el-tag>
                                <br>
                            </span>
                            articleID:
                            <br>
                            <el-tag disable-transitions size="medium" type="info" hit>{{ scope.row.id }}</el-tag>
                            <br>
                            获取日期:
                            <br>
                            <el-tag disable-transitions size="medium" type="info" hit>
                                {{formatDate(scope.row.createtime)}}
                            </el-tag>
                            <br>
                            发布时间:
                            <br>
                            <el-tag disable-transitions size="medium" type="info" hit>{{
                                formatDate(scope.row.publishtime) }}
                            </el-tag>
                        </div>
                    </el-card>
                </template>
            </el-table-column>

            <el-table-column
                    prop="logo"
                    label="预览图"
                    width="200">
                <template slot-scope="scope">
                    <a :href="scope.row.logo" target="_blank">
                        <img :src="scope.row.logo" width="190">
                    </a>
                </template>
            </el-table-column>

            <el-table-column
                    prop="subject"
                    label="内容标题"
                    width="250"
                    show-overflow-tooltip>
            </el-table-column>
            <el-table-column
                    prop="summary"
                    label="摘要"
            >
                <template slot-scope="scope">
                    <p @click='tableClickHandler(scope.row)' style="cursor:pointer">{{scope.row.summary || '无摘要'}}</p>
                </template>
            </el-table-column>

            <el-table-column
                    prop="operation"
                    label="操作区"
                    width="180"
            >
                <template slot-scope="scope">
                    <el-button
                            style="margin:0"
                            plain round
                            @click="handleManage(scope.row)">管理
                    </el-button>
                </template>
            </el-table-column>
        </el-table>
    </div>
</template>

<script>
    import dayjs from 'dayjs'

    export default {
        name: 'ContentTable',
        props: {
            previewInfo:{
               /* bannerarticle:{},
                recommendarticles:[],*/
            },
        },
        data() {
            return {
                currentRow: null,
            }
        },
        mounted() {

        },
        methods: {
            // 切换到文章管理,并拉取搜索此日期的文章
            handleManage(row){
                this.$bus.$emit('contentHandler', {
                    func: 'findPreview',
                    args: {
                        time: row.createtime*1000,
                        topicId:row.topicid,
                        articleId:row.id,
                    }
                })
            },
            formatDate(time) {
                let date = dayjs(time * 1000)
                return date.format('YYYY年M月D日  h:mm ')
            },
            handleCurrentChange(val) {
                this.currentRow = val;
            },
            tableClickHandler(row) {
                window.open(row.url)
            },

        },
        computed: {
            // 将banner放在第一篇文章的位置
            allArticle() {
                return [this.previewInfo.bannerarticle].concat(this.previewInfo.recommendarticles)
            }
        }
    }
</script>

<style scoped>

</style>
