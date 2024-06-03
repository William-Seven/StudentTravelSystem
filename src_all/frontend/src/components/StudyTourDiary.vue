<!-- StudyTourDiary.vue -->
<template>
    <div class="background"></div>
    <form class="form">
        <div class="study-tour-diary">
            <h1 class="title">游学日记</h1>
            <button class="return_button" @click.prevent="goToDashboard">返回首页</button>
            <!-- 四个搜索框 -->
            <div class="input-container">
                <input class="input1" type="text" v-model="searchTitle" placeholder="搜索标题">
                <input class="input2" type="text" v-model="searchAuthor" placeholder="搜索作者名">
                <input class="input3" type="text" v-model="searchDescription" placeholder="搜索目的地">
                <input class="input4" type="text" v-model="searchContent" placeholder="搜索内容">
            </div>
            <!-- 排序选择 -->
            <div class="choose-container">
                <label for="sort">排序方式:</label>
                <select id="sort" v-model="sort">
                    <option value='0'>热度</option>
                    <option value='1'>评分</option>
                </select>
            </div>
            <!-- 搜索按钮 -->
            <button class="search_button" @click.prevent="searchDiaries">搜索</button>
            <!-- 下载按钮，仅在有日记时显示 -->
            <button class="download_button" v-if="diaries.length" @click.prevent="downloadDiaries">下载日记</button>
            <!-- 游学日记列表 -->
            <ul v-if="diaries.length" class="diary-list">
                <li v-for="diary in diaries" :key="diary.title" class="diary-item">
                    <p>标题：{{ diary.title }}</p>
                    <p>作者：{{ diary.author }}</p>
                    <p>描述对象：{{ diary.description }}</p>
                    <p>热度：{{ diary.popularity }}</p>
                    <p>评分：{{ diary.rating }}</p>
                    <button @click.prevent="goToDiaryDetail(diary)">详情</button>
                </li>
            </ul>
            <p class="error" v-else>没有找到相关日记。</p>
            <!-- 写日记按钮 -->
            <button class="write_button" @click.prevent="goToWriteDiary">写日记</button>
        </div>
    </form>
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
                // 在发送请求之前打印搜索关键字
                console.log('搜索标题:', searchTitle.value);
                console.log('搜索作者:', searchAuthor.value);
                console.log('搜索描述对象:', searchDescription.value);
                console.log('搜索内容:', searchContent.value);
                console.log('排序方式:', sort.value);

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

        // 下载日记
        const downloadDiaries = async () => {
            try {
                const response = await axios.post('/api/diary-download');
                if (response.data.success) {
                    // 下载成功，显示提示信息
                    showDownloadSuccess();
                } else {
                    // 下载失败，显示错误信息
                    console.error('下载失败:', response.data.message);
                }
            } catch (err) {
                console.error('下载时发生错误:', err);
            }
        };

        // 显示下载成功的提示信息，并提供解压选项
        const showDownloadSuccess = () => {
            // 这里可以使用模态框或者弹窗来显示提示信息
            // 以下代码仅为示例，具体实现可能需要使用模态框组件
            alert('压缩下载成功，是否解压？');
            const userChoice = confirm('压缩下载成功，请输入压缩文件的路径，如D:\\\\Diarytemp.zlx');
            if (userChoice) {
                // 用户选择“是”，提示输入解压路径
                const path = prompt('请输入压缩文件的路径，如D:\\\\Diarytemp.zlx');
                if (path) {
                    // 用户输入了解压路径，调用后端解压接口
                    uncompressDiaries(path);
                }
            }
        };

        // 解压日记
        const uncompressDiaries = async (path) => {
            try {
                const response = await axios.post('/api/diary-uncompress', {
                    path: path,
                });
                if (response.data.success) {
                    // 解压成功
                    alert('解压成功');
                    console.log('解压成功');
                } else {
                    // 解压失败，显示错误信息
                    console.error('解压失败:', response.data.message);
                }
            } catch (err) {
                console.error('解压时发生错误:', err);
            }
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
            downloadDiaries,
        };
    },
};
</script>

<style scoped>
.background {
    position: absolute;
    width: 100%;
    height: 100%;
    margin: 0;
    padding: 0;
    background-attachment: fixed;
    overflow: hidden;
    background-image: url('~@/assets/img/diaryhome.png');
    background-size: cover;
}

.background::before {
    content: "";
    position: fixed;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    background-image: url('~@/assets/img/diaryhome.png');
    background-size: cover;
    background-attachment: fixed;
    z-index: -1;
    /* 确保背景层在内容层之下 */
}

.form {
    position: absolute;
    transform: translate(-50%, 0%);
    padding: 2%;
    top: 3%;
    left: 50%;
    width: 45%;
    min-height: 500px;
    background: rgba(255, 255, 255, 0.2);
    backdrop-filter: blur(10px);
    border-radius: 20px;
    /* 设置圆角为20像素 */
    /* 其他样式，例如边框、阴影等 */
    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
    /* 添加轻微的阴影效果 */
}

.title {
    color: #fefefe;
    font-size: 4em;
    /* 设置字号大小 */
    margin: 0%;
    font-family: 'STKaiti', 'KaiTi', sans-serif;
    /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
    max-width: 80%;
    margin-top: 0vh;
    text-align: center;
    margin-left: auto;
    /* 左外边距自动 */
    margin-right: auto;
    /* 右外边距自动 */
    margin-bottom: 0.5em;
}

button {
    justify-content: space-between;
    margin: auto;
    font-size: 1em;
    border: 1px solid #000;
    /* 边框样式，可以根据需要调整 */
    cursor: pointer;
    /* 鼠标悬停时显示指针手势 */
    border-radius: 8px;
    /* 添加圆角 */
}

button:hover {
    background-color: #56cfcf;
}

.return_button {
    transform: translate(-50%, -50%);
    position: absolute;
    top: 2em;
    left: 10%;
}

.input1,
.input2,
.input3,
.input4 {
    color: #000000;
    font-size: 1em;
    font-family: 'STKaiti', 'KaiTi', sans-serif;
    position: relative;
    width: 20%;
    border-radius: 8px;
    /* 添加圆角 */
    margin-left: 1em;
}

.input-container {
    text-align: center;
    margin-left: auto;
    /* 左外边距自动 */
    margin-right: auto;
    /* 右外边距自动 */
}

.choose-container {
    text-align: center;
    margin-left: auto;
    /* 左外边距自动 */
    margin-right: auto;
    /* 右外边距自动 */
    color: #fefefe;
    margin: 0%;
    font-family: 'STKaiti', 'KaiTi', sans-serif;
    /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
    margin-top: 1em;
}

.search_button {
    text-align: center;
    font-size: 1.5em;
    margin-top: 0.5em;
    margin-left: auto;
    /* 左外边距自动 */
    margin-right: auto;
    /* 右外边距自动 */
    display: block;
}

.write_button {
    text-align: center;
    font-size: 1.5em;
    margin-top: 0.5em;
    margin-left: auto;
    /* 左外边距自动 */
    margin-right: auto;
    /* 右外边距自动 */
    display: block;
}

.diary-item {
    color: #fefefe;
    margin-bottom: 3em;
}

.error {
    color: #fefefe;
    font-size: 2em;
    /* 设置字号大小 */
    font-family: 'STKaiti', 'KaiTi', sans-serif;
    /* 优先使用华文楷体，如果不可用则使用无衬线字体 */
    max-width: 80%;
    text-align: center;
    margin-left: auto;
    /* 左外边距自动 */
    margin-right: auto;
    /* 右外边距自动 */
    margin-bottom: 2vh;
}
</style>