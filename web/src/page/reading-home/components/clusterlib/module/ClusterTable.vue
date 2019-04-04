<template>
    <el-table
            border
            :data="clusterinfos.infos"
            :row-class-name="specialClass"
            style="width: 100%;">
        <el-table-column
                prop="order"
                label="首页Tab顺序"
                width="110">
            <template slot-scope="scope">
                <el-input-number
                        style="width: 88px;"
                        size="mini"
                        v-model="scope.row.sortid"
                        @change="sortChange(scope.row)"
                        :step="1"
                        :precision="0"
                        :min="1"
                ></el-input-number>
            </template>
        </el-table-column>
        <el-table-column
                prop="name"
                label="卡片名称"
                width="180"
        >
        </el-table-column>
        <el-table-column
                prop="annotation"
                label="特殊标示"
                width="130"
        >
            <template slot-scope="scope">
                {{annotation(scope.row)}}
            </template>
        </el-table-column>
        <el-table-column
                align="center"
                prop="connect"
                label="关联一级标签"
        >
            <template slot-scope="scope">
                <el-tag style="margin-right:10px" disable-transitions
                        v-for="(item,index) in tagidsHandler(scope.row.tags,1)">{{ item.name }}
                </el-tag>
            </template>
        </el-table-column>
        <el-table-column
                align="center"
                prop="status"
                label="当前状态"
                width="100"
        >
            <template slot-scope="scope">
                <el-tag style="margin-right:10px" disable-transitions hit :type="statusType(clusterStatus(scope.row))"
                        size="medium">{{ clusterStatus(scope.row) }}

                </el-tag>
            </template>
        </el-table-column>
        <el-table-column
                align="center"
                prop="articlenum"
                label="文章数量"
                width="60"
        >
            <template slot-scope="scope">
                <el-tag style="margin-right:10px" disable-transitions hit
                        size="mini">{{ scope.row.articlenum }}

                </el-tag>
            </template>
        </el-table-column>
        <el-table-column label="操作" width="150">
            <template slot-scope="scope">
                <el-button
                        :disabled="isSpecialCluster(scope.row)"
                        size="mini"
                        @click="handleEdit(scope.$index, scope.row)">编辑
                </el-button>
                <el-button
                        :disabled="isSpecialCluster(scope.row)"
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
        name: "ClusterTable",
        props: {
            clusterinfos: {
                type: Object,
                default: {
                    infos: []
                }
            },
            taglist: {},
            clusterFlag: {
                /*eXMBookClusterInfoFlagIsRuning: 0x01, // 运营中
                eXMBookClusterInfoFlagIsOffTheShelved: 0x02, // 下线了
                eXMBookClusterInfoFlagIsRecommendMon: 0x04, // 周一推荐
                eXMBookClusterInfoFlagIsRecommendTUE: 0x08, // 周二推荐
                eXMBookClusterInfoFlagIsRecommendWED: 0x10, // 周三推荐
                eXMBookClusterInfoFlagIsRecommendTHU: 0x20, // 周四推荐
                eXMBookClusterInfoFlagIsRecommendFRI: 0x40, // 周五推荐
                eXMBookClusterInfoFlagIsSpecialCluster: 0x80, // 特殊卡片(屏蔽掉编辑)*/
            }
        },
        data() {
            return {
                tagMap: {        //加快tag匹配速度
                    tagMap1: {},
                    // tagMap2: {}
                },
            }
        },
        mounted() {
            this.tagMap.tagMap1 = this.list2Map(this.taglist.taglist1)
        },
        watch: {
            taglist: {
                deep: true,
                handler: function () {
                    this.tagMap.tagMap1 = this.list2Map(this.taglist.taglist1)
                }
            }
        },
        methods: {
            specialClass(scope) {
                if (this.isSpecialCluster(scope.row)) {
                    return 'success-row';
                } else {
                    return ''
                }
            },
            annotation(cluster){
                if (this.isSpecialCluster(cluster)) {
                    if (this.flagIs(cluster,this.clusterFlag.eXMBookClusterInfoFlagIsRecommendMon)) {
                        return '周一推荐'
                    }else if (this.flagIs(cluster,this.clusterFlag.eXMBookClusterInfoFlagIsRecommendTUE)) {
                        return '周二推荐'
                    }else if (this.flagIs(cluster,this.clusterFlag.eXMBookClusterInfoFlagIsRecommendWED)) {
                        return '周三推荐'
                    }else if (this.flagIs(cluster,this.clusterFlag.eXMBookClusterInfoFlagIsRecommendTHU)) {
                        return '周四推荐'
                    }else if (this.flagIs(cluster,this.clusterFlag.eXMBookClusterInfoFlagIsRecommendFRI)) {
                        return '周五推荐'
                    } else {
                        return ''
                    }
                } else {
                    return ''
                }
            },
            isSpecialCluster(cluster) {
                return this.flagIs(cluster,this.clusterFlag.eXMBookClusterInfoFlagIsSpecialCluster)
            },
            sortChange(row) {
                this.$bus.$emit('clusterHandler', {
                    func: 'sendUpdateCluster',
                    args: {
                        func: 8,
                        updateclusterinforeq: JSON.stringify({
                            clusterinfo: {
                                id: row.id,
                                sortid: row.sortid,
                            }
                        })
                    },
                });
            },
            statusType(status) {
                switch (status) {
                    case '未发布':
                        return 'info';
                    case '运营中':
                        return 'success';
                    case '已下线':
                        return 'danger';
                    default:
                        return '';
                }
            },
            // 判断此的flag的某个值是否为1
            flagIs(cluster,flag) {
                return (cluster.flag & flag) === flag
            },
            clusterStatus(cluster) {
                // 运营中
                if (this.flagIs(cluster,this.clusterFlag.eXMBookClusterInfoFlagIsRuning)) {
                    return '运营中'
                } else if (this.flagIs(cluster,this.clusterFlag.eXMBookClusterInfoFlagIsOffTheShelved)) {
                    // 已下线
                    return '已下线'
                } else {
                    return '未发布'
                }
            },
            handleEdit(index, row) {
                let args = {...row}
                args.tagSelect1 = this.tagidsHandler(row.tags, 1)
                this.$bus.$emit('clusterHandler', {
                    func: 'editClusterTagBox',
                    args: args
                })
            },
            handleLog(index, row) {
                console.log(index, row);
                //this.$parent.deleteTag({id:row.id})
            },
            // 将指定级别的tag,从id返回完成info
            tagidsHandler(tags, itemLevel) {
                let tagIds
                if (tags && tags.leveldatas) {
                    let levelItem = tags.leveldatas.find(item => {
                        return item.level === itemLevel
                    })
                    if (levelItem && Array.isArray(levelItem.tagids)) {
                        tagIds = levelItem.tagids;
                    } else {
                        return null
                    }
                }
                let tagMap = this.tagMap['tagMap' + itemLevel]
                return this.matchMap(tagIds, tagMap) || {}
            },
            matchMap(keyList, map) {
                let distList = []
                if (map.size < 1 || !keyList) {
                    return []
                }
                for (let item of keyList) {
                    distList.push(map.get(item) || {})
                }
                return distList
            },
            list2Map(list, key = 'id') {
                let map = new Map()
                for (let item of list) {
                    map.set(item[key], item)
                }
                return map
            },
        }
    }
</script>

<style>
    .el-input-number.is-controls-right .el-input__inner {
        padding: 0px 30px 0px 0px;
    }
</style>
