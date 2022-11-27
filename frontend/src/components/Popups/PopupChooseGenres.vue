<script setup>
import Popup from './Popup.vue';
</script>

<template>
  <Popup>
    <div class="v-popupChooseGenres">
      <div class="v-popupChooseGenres__text">Выберите жанр фильма</div>
      <div class="buttonWrapper">
        <v-btn
          v-for="type in types"
          :key="type.id"
          @click="watchFilm(type.id)"
          color="primary"
          class="buttonOfType">
          {{ type.title }}
        </v-btn>
      </div>
    </div>
  </Popup>
</template>

<script>
import api from '../../mixins/api';
export default {
  components: {
    Popup,
  },
  mixins: [api],
  props: {
    usersId: {
      type: Array,
    }
  },
  data() {
    return {
      types: [],
    };
  },
  methods: {
    // функция отправляет на сервер id пользователей из группы и айди жанра фильма
    watchFilm(id) {
      this.apiPost(``)
    },

    async getGenres() {
      return this.apiPost(``)
    }
  },
  mounted() {
    this.types = this.getGenres()
  }
};
</script>

<style>
.v-popupChooseGenres {
  color: black;
  width: 40rem;
  height: 30rem;
  padding: 2rem;
}
.v-popupChooseGenres__text {
  margin-bottom: 2rem;
}
.buttonWrapper {
  display: flex;
  flex-direction: column;
  align-items: stretch;
}
.buttonOfType {
  margin-bottom: 1rem;
}
</style>
