<script setup>
import api from '../../mixins/api.js';
import { RouterLink } from 'vue-router';
</script>

<template>
  <main class="browser">
    <section class="popular">
      <h2 class="subTitle">Популярно сейчас</h2>
      <div class="movieCards popularWrap">
        <div
          class="movieCard popularMovie"
          v-for="(movie, index) in popularMovies"
          :key="index">
          <RouterLink :to="`/movie/${movie.id}`">
            <img
              :src="movie.poster_url"
              class="movieCard__cover" />
            <div class="movieCard__rateBar">{{ Math.round(movie.rate * 10) / 10 }}</div>
            <div class="movieCard__footer">
              <span class="movieCard__name">{{ movie.name.length > 16 ? `${movie.name.slice(0, 16)}...` : movie.name }}</span>
              &nbsp;
              <span class="movieCard__year">({{ movie.year }})</span>
            </div>
          </RouterLink>
        </div>
      </div>
    </section>
    <section class="selected"></section>
  </main>
</template>

<script>
export default {
  mixins: [api],
  components: [RouterLink],
  data() {
    return {
      popularMovies: [],
    };
  },
  mounted() {
    this.getMovies();
  },
  methods: {
    async getMovies() {
      const response = await this.apiPost('content/fetch');
      this.popularMovies = response.additional.movies;
    },
  },
};
</script>

<style scoped>
.subTitle {
  margin-left: 50px;
  margin-bottom: 35px;
}
.movieCards {
  padding: 0 32px;
  display: grid;
  grid-template-columns: repeat(5, 194px);
  grid-auto-rows: auto;

  gap: 16px;
}

.movieCard {
  display: flex;
  flex-direction: column;

  border-radius: 4px;
}

.movieCard__cover {
  width: 194px;
  height: 270px;
  position: relative;
  border-radius: 4px 4px 0 0;

  background: #c0c0c0;
}

.movieCard__year {
  color: #e1e1e1;
}

.movieCard__rateBar {
  width: 56px;
  height: 20px;
  position: absolute;
  bottom: 56px;
  right: 8px;
  border-radius: 4px;
  text-align: center;
  font-size: 14px;
  color: #292929;
  background: #85d982;
}

.movieCard__footer {
  display: flex;
  padding: 12px;
  background: #1f1f1f;
  border-radius: 0 0 4px 4px;
}

.movieCard__name {
  flex-grow: 1;
}
</style>
