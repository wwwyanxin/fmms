<template>
    <div>
        wyx
        <img class="img">
        <el-row>
            <el-button>默认按钮</el-button>
            <el-button type="primary">主要按钮</el-button>
            <el-button type="success">成功按钮</el-button>
            <el-button type="info">信息按钮</el-button>
            <el-button type="warning">警告按钮</el-button>
            <el-button type="danger">危险按钮</el-button>
        </el-row>
        <h1>{{textTest}}</h1>
    </div>
</template>

<script>
    import {cloneDeep,getUrl} from '@/lib/util'
    import Api from '@/service/api.js'

    export default {
        name: "Member",
        data(){
            return {
                textTest : "",
            }
        },
        created() {},
        beforeDestroy() {},
        async mounted(){
            const res = await Api.get('/fmms/cgi-bin/logicsvr.cgi/test', {
                a:1,
                b:2,
                c:3
            })
            this.textTest = res;
            console.log(res);
        },
        methods:{

        },
        computed:{

        }
    }
</script>

<style scoped>
    div{
        background: pink;
        color:olivedrab;
    }

    .img{
        transform:rotate(17deg);
        background-image: url(../../../style/images/game.png);
        width:46px;
        height:45px;
    }

</style>
