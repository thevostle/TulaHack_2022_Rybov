<template>
  <Popup>
    <div class="v-popupChooseGenres">
        <div class="v-popupChooseGenres__text">Выберите жанр фильма</div>
    </div>
  </Popup>
</template>

<script>
import Popup from './Popup.vue'

export default {
    components: {
        Popup
    }
}
</script>

<style>
.v-popupChooseGenres {
  color: black;
  width: 40rem;
  height: 30rem;
  padding: 2rem;
}
</style>