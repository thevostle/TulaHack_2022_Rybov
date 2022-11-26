<script setup>
import api from '../mixins/api';
import Aside from '../components/layout/Aside.vue';
</script>

<template>
  <div>
    <Aside />
    <div class="userProfile wrapper">
      <div>
        Профиль {{ login }}
        <v-table density="compact">
          <thead>
            <tr>
              <th class="text-left">Название</th>
              <th class="text-left">Оценка</th>
              <th class="text-center"></th>
            </tr>
          </thead>
          <tbody>
            <tr
              v-for="item in movies"
              :key="item.title">
              <td>
                <a :href="item.link">{{ item.title }}</a>
              </td>
              <td>
                <input
                  type="text"
                  v-model="item.rating" />
              </td>
              <td>
                <div
                  class="deleteMovie"
                  @click="deleteMovie(item.id)">
                  x
                </div>
              </td>
            </tr>
          </tbody>
        </v-table>
        <v-btn
          color="secondary"
          @click="saveMovies">
          Сохранить
        </v-btn>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  components: {
    Aside,
  },
  mixins: [api],
  data() {
    return {
      userId: 0,
      login: '',
      movies: [
        {
          id: 42,
          title: 'Властелин колец',
          rating: 10,
          link: '',
        },
        {
          id: 626,
          title: 'Игра престолов',
          rating: 10,
          link: '',
        },
        {
          id: 51,
          title: 'Атака титанов',
          rating: 10,
          link: '',
        },
        {
          id: 95562,
          title: 'Звездные войны 3',
          rating: 9,
          link: '',
        },
        {
          id: 5314,
          title: 'Токийский гуль',
          rating: 8,
          link: '',
        },
      ],
    };
  },
  updated() {
    this.getUser();
  },
  methods: {
    async getUser() {
      this.userId = this.$route.params.userId;
      const userData = await this.apiGet('user/get', { id: this.userId });
      this.login = this.userId; // userData.login
    },
    deleteMovie(id) {
      this.movies = this.movies.filter(function (obj) {
        return obj.id !== id;
      });

      this.saveMovies();
    },
    // отправить результат на сервер
    async saveMovies() {
      await this.apiPost(`movies/set/${this.userId}`, this.movies)
    },
  },
};
</script>

<style lang="scss">
.wrapper {
  max-width: 120rem;
}

.deleteMovie {
  cursor: pointer;
  &:hover {
    color: orange;
  }
}
</style>
