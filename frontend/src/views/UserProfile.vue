<script setup>
import api from '../mixins/api';
import Aside from '../components/layout/Aside.vue';
</script>

<template>
  <div>
    <Aside />
    <div class="userProfile wrapper">
      <div>
        <div class="userProfile__title">Профиль {{ login }}</div>
        <div class="userProfile__stats">
          <div class="userProfile__statsItem">
            <div class="userProfile__statsItemData">Всего просмотрено: {{ getMoviesLenght }}</div>
          </div>
        </div>
        <v-table class="userProfile__table">
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
              :key="item.name">
              <td>
                <a :href="item.link">{{ item.name }}</a>
              </td>
              <td>
                <input
                  class="input__rating"
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
      moviesIds: [],
      movies: [],
    };
  },
  methods: {
    async getUser() {
      this.userId = this.$route.params.userId;
      const userData = await this.apiPost('user/get/by_id', { id: this.userId });
      this.login = userData.additional.login;
    },
    async getMovie(id) {
      const movieData = await this.apiPost('content/get', { id: id });
      return movieData.additional;
    },
    async getMovies() {
      const moviesData = await this.apiPost(`user/${this.userId}/rates/fetch`);
      this.movies = moviesData.additional.rates.map(async (movie) => {
        const fetchedMovie = await this.getMovie(movie.movieId);
        return ({ ...fetchedMovie, rating: movie.userRate });
      });
    },
    async deleteMovie(id) {
      this.movies = this.movies.filter(function (obj) {
        return obj.id !== id;
      });
    },
  },
  computed: {
    getMoviesLenght() {
      return this.movies.length;
    },
  },
  mounted() {
    this.getUser();
    this.getMovies();
  },
};
</script>

<style lang="scss">
.wrapper {
  max-width: 80rem;
}

.deleteMovie {
  cursor: pointer;
  &:hover {
    color: orange;
  }
}

.userProfile {
  margin: 0 auto;
  padding-top: 3rem;
}

.userProfile__title {
  font-size: 1.4rem;
  margin-bottom: 1rem;
}

.userProfile__stats {
  margin-bottom: 1rem;
}

.userProfile__statsItem {
  display: flex;
}

.userProfile__table {
  margin-bottom: 2rem;
}

.input__rating {
  background-color: rgb(59, 59, 59);
  text-align: center;
  width: 3rem;
}
</style>
