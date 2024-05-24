<!-- StudyTourDiary.vue -->
<template>
    <div class="study-tour-diary">
        <h1>游学日记</h1>
        <button @click="goToDashboard">返回首页</button>
        <!-- 四个搜索框 -->
        <div>
            <input type="text" v-model="searchTitle" placeholder="搜索标题">
            <input type="text" v-model="searchAuthor" placeholder="搜索作者名">
            <input type="text" v-model="searchDescription" placeholder="搜索描述对象">
            <input type="text" v-model="searchContent" placeholder="搜索内容">
        </div>
        <!-- 排序选择 -->
        <div>
            <label for="sort">排序方式:</label>
            <select id="sort" v-model="sort">
                <option value='0'>热度</option>
                <option value='1'>评分</option>
            </select>
        </div>
        <!-- 搜索按钮 -->
        <button @click="searchDiaries">搜索</button>
        <!-- 游学日记列表 -->
        <ul v-if="diaries.length" class="diary-list">
            <li v-for="diary in diaries" :key="diary.title" class="diary-item">
                <p>标题：{{ diary.title }}</p>
                <p>作者：{{ diary.author }}</p>
                <p>描述对象：{{ diary.description }}</p>
                <p>热度：{{ diary.popularity }}</p>
                <p>评分：{{ diary.rating }}</p>
                <button @click="goToDiaryDetail(diary)">详情</button>
            </li>
        </ul>
        <p v-else>没有找到相关日记。</p>
        <!-- 写日记按钮 -->
        <button @click="goToWriteDiary">写日记</button>
    </div>
</template>

<script>
import { ref } from 'vue';
import axios from 'axios';
import { useRouter } from 'vue-router';

export default {
    name: 'StudyTourDiary',
    setup() {
        const router = useRouter();
        const searchTitle = ref('');
        const searchAuthor = ref('');
        const searchDescription = ref('');
        const searchContent = ref('');
        const sort = ref('1'); // 默认按照热度排序
        const diaries = ref([]); // 存储日记列表
        let currentDiary = ref({}); // 用于累积当前日记的数据

        // 搜索日记
        const fetchDiaries = async () => {
            try {
                const response = await axios.post('/api/diary-search', {
                    title: searchTitle.value || '-1',
                    author: searchAuthor.value || '-1',
                    description: searchDescription.value || '-1',
                    content: searchContent.value || '-1',
                    sort: sort.value,
                });

                const list = response.data.list.split('\n');
                for (let i = 0; i < list.length; i++) {
                    if (i % 3 === 0) {
                        // 每三行是一个新日记的开始
                        if (currentDiary.value.title) {
                            // 如果当前日记已经存在，推入日记数组
                            diaries.value.push(currentDiary.value);
                        }
                        currentDiary.value = {
                            title: list[i].split(' ')[0], // 标题
                            author: list[i].split(' ')[1], // 作者
                            description: list[i].split(' ')[2], // 描述对象
                            content: '', // 内容将在下一行被填充
                            popularity: 0, // 热度和评分将在第三行被填充
                            rating: 0,
                        };
                    } else if (i % 3 === 1) {
                        // 第二行是日记内容
                        currentDiary.value.content = list[i].trim();
                    } else if (i % 3 === 2) {
                        // 第三行是热度和评分
                        const [popularity, rating] = list[i].split(' ');
                        currentDiary.value.popularity = parseInt(popularity, 10);
                        currentDiary.value.rating = parseFloat(rating);
                    }
                }
                // 推入最后一个日记到数组
                if (currentDiary.value.title) {
                    diaries.value.push(currentDiary.value);
                }
            } catch (err) {
                console.error('Error searching diaries:', err);
            }
        };

        const searchDiaries = () => {
            diaries.value = [];
            fetchDiaries();
        };

        // 跳转到日记详情页面
        const goToDiaryDetail = (diary) => {
            router.push({
                path: '/diary-detail',
                query: { diary: JSON.stringify(diary) },
            });
        };

        // 跳转到写日记页面
        const goToWriteDiary = () => {
            router.push('/write-diary');
        };

        // 跳转到首页
        const goToDashboard = () => {
            router.push('/dashboard');
        };

        return {
            searchTitle,
            searchAuthor,
            searchDescription,
            searchContent,
            sort,
            diaries,
            searchDiaries,
            goToDiaryDetail,
            goToWriteDiary,
            goToDashboard,
        };
    },
};
</script>