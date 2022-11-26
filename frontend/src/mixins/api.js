export default {
  data() {
    return {
      apiUrl: 'http://1157-94-28-235-94.eu.ngrok.io/',
    };
  },
  methods: {
    async apiPost(action, data) {
      const payload = new URLSearchParams();

      for (const prop in data) {
        payload.append(prop, data[prop]);
      }

      const options = {
        method: 'POST',
        mode: 'no-cors',
        headers: {
          'Content-Type': 'application/x-www-form-urlencoded',
        },
        body: payload,
      };

      try {
        const response = await fetch(`${this.apiUrl}${action}`, options);

        if (response.ok) {
          const data = await response.json();
          return data;
        }
      } catch (error) {
        return error;
      }
    },
    async apiGet(action, data) {
      const payload = new URLSearchParams();

      for (const prop in data) {
        payload.append(prop, data[prop]);
      }

      const options = {
        method: 'GET',
        mode: 'no-cors',
      };

      try {
        const response = await fetch(`${this.apiUrl}${action}?${payload}`, options);

        if (response.ok) {
          const data = await response.json();
          return data;
        }
      } catch (error) {
        return error;
      }
    },
  },
};
