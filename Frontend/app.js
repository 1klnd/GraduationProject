const App = {
    data() {
       return {
          server: 'https://localhost:8899/',
          statuscode: 200,
          temperatureSV: 0,
          humiditySV: 0,
          timeFrom: '2018-08-18T07:22:16.0000000Z',
          timeTo: '2022-08-18T07:22:16.0000000Z',
          SVs: null,
          MVs: null,
          develop: false,
       }
    },


    methods: {
       updateSV() {
          if (confirm("Change SV ?\n\n" +
             "Temperature:" + this.temperatureSV +
             "\nHumidity" + this.humiditySV) == true) {
             if (this.validateSV()) {
                if (this.pushSV()) {
                   alert("SV Changed")
                   return true
                }
                else {
                   alert("Changing SV failed\nPlease retry later")
                   return false
                }
             }
             else {
                alert("Invalid SV")
                return false
             }
          }
          else {
             return false
          }
       },

       validateSV() {
          /* TODO */
          return true
       },

       pushSV() {
          axios.post(this.server + 'api/SettingValue?' +
             'temperature=' + this.temperatureSV +
             '&humidity=' + this.humiditySV
          )
             .then(r => this.statuscode = r.data.status)
             .catch(error => console.log(error));
          return this.statuscode == 200 ? true : false
       },

       getSV() {
          axios.get(this.server + 'api/SettingValue')
             .then(
                response => {
                   this.temperatureSV = response.data.temperature
                   this.humiditySV = response.data.humidity
                }
             )
             .catch(error => console.log(error));
          return this.statuscode == 200 ? true : false
       },

       getSVs() {
          axios.get(this.server + 'api/SettingValues?' +
             'from=' + this.timeFrom +
             '&to=' + this.timeTo
          )
             // ?from=2018-08-18T07:22:16.0000000Z&to=2028-08-18T07:22:16.0000000Z
             .then(
                response => this.SVs = response.data
             )
             .catch(error => console.log(error));
          return this.statuscode == 200 ? true : false
       },

       getMVs() {
          axios.get(this.server + 'api/MeasuredValues?' +
             'from=' + this.timeFrom +
             '&to=' + this.timeTo
          )
             // ?from=2018-08-18T07:22:16.0000000Z&to=2028-08-18T07:22:16.0000000Z
             .then(
                response => this.MVs = response.data
             )
             .catch(error => console.log(error));
          return this.statuscode == 200 ? true : false
       },

       refresh() {
          this.getSVs()
          this.getMVs()
          window.SVs = this.SVs
          console.log(this.SVs)
       }

    },

    mounted() {
       this.getSV()
    }
 }

 Vue.createApp(App).mount('#app')