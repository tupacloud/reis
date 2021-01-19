app.component('history-display', {
    data() {
        return {
            data: [],
            labels: [],
            isFetching: true
        }
    },
    props: {
        type: {
            type: String,
            required: true
        },
        id: {
            type: Number,
            required: true
        }
    },
    template:
        /*html*/
        `
    <div class="display">
    
        <div :id='loaderName'><img src="assets/loaders/gear2.svg" /></div>
        <history-content v-if="!isFetching" :id="tagName" :data="data" :labels="labels"></history-content>

    </div>
    `,
    computed: {
        loaderName() {
            return 'loader' + this.id
        },
        tagName() {
            return 'chart' + this.id
        }
    },
    mounted: function () {

            var setValues = this.setValues;
            var scale_by_day = this.scale_by_day;

            if (this.type == 'dias') {

                this.getValues(this.loaderName).then(function (res) {

                    var data = scale_by_day(res);
                    var dados = data.map(el => el.mean);
                    var rotulos = data.map(el => el.label);

                    setValues(dados, rotulos);

                });

            }
            else if (this.type == 'all') {

                this.getValues(this.loaderName).then(function (res) {

                    var data = res.filter(el => el.measure > 0).map((el) => el.measure);
                    var labels = res.filter(el => el.measure > 0).map((el) => el.date);

                    setValues(data, labels);
                });

            }
        

    },
    methods: {
        setValues(data, labels) {
            this.data = data
            this.labels = labels
            this.isFetching = false
            this.alreadyMounted = true
        },
        getValues(loaderName) {

            return new Promise(function (resolve, reject) {

                const API_ENDPOINT = "https://mushroom.api.tupacloud.com/";
                var ms, data, labels;
                var input = '&INPUT={wBeeName: "caixa preta", lastMeasure: [{date:"2020-12-01T13:03:24.472Z"}], cid: "cid_00", dbs: "besouro", col: "clients"}'
                var flow = 'FLOW=%7B%22flush%22%3A%22S0ydU20FEAO%2Bsb1oCBItR3CP7tw6umayvMPpkBwJFJN5VNh9ncekEJWFYJ8nrfrc0n8JgX3E%2B36L8LFueZO1KA%3D%3D%22%2C%22i' +
                    'ntegrity%22%3A%2250aee3d861fc78e96ab7587c9dd16fbf%22%2C%22security_token%22%3A%222b9093f71f43ffdf6eaf31445253cb1d98af1241fdee2e611' +
                    '3b3948510e847aba4e3e6061304f3213e402a0fd7a6d07495dfcdedfe02290d7bdbfb8f424a206aaefedfd1b9f858133e3c96ce4864080acc288738cf4404aed0c' +
                    'cccee8ab6c5e9e3f1487c613c6c840d43776ee0e1e703ebbb377999f98c9f0f62abe3f5d45e623a8538b606df9a8cef4377345df5637669565d1aed4f31de629a3' +
                    '9fa4b7593e30e3cfbfae348f6d3c123261ebc0a110943665a9636c671eb81152b62e038499f30eb63f6301401f4471902045caf046b907219d9f76e4283e11f84c' +
                    '88781d66b3b0fe9df3fc506a5034eb02dd77cb67b56d8c83596a82edca9677eca8a0e9b6a%22%7D';
                var flush = flow + input;


                console.log('ueueeee', loaderName)
                jQuery.ajax({
                    type: "POST",
                    crossdomain: true,
                    cache: false,
                    beforeSend: function () {
                        $('#' + loaderName).show();
                    },
                    url: API_ENDPOINT,
                    data: { URL: flush },
                    complete: function () {
                        console.log('#' + loaderName)
                        $('#' + loaderName).hide();
                    },
                    success: function (res) {

                        ms = JSON.parse(res).sort((a, b) => new Date(a.date) - new Date(b.date));

                        data = ms.filter(el => el.measure > 0).map((el) => el.measure);
                        labels = ms.filter(el => el.measure > 0).map((el) => el.date);

                        resolve(ms);

                    }
                });

            }

            )

        },
        scale_by_day(dt) {

            var dt = dt.filter(el => el.measure > 0); // remove 0s. retirar essa linha no futuro
            var groupByYear = this.groupBy(dt, x => new Date(x.date).getFullYear());
            var groups = [];
            var data = [];


            Map.prototype.forEach.call(groupByYear, el => {
                groups.push(this.groupBy(el, x => 2 ** (new Date(x.date).getDate()) * 3 ** (new Date(x.date).getMonth() + 1)));
            });

            Array.prototype.forEach.call(groups, year => {
                data.push([]);
                Map.prototype.forEach.call(year, el => {

                    var month = new Date(el[0].date).getMonth() + 1;
                    var label = new Date(el[0].date).getDate() + '/' + month + '/' + new Date(el[0].date).getFullYear();
                    data[data.length - 1].push({ "label": label, "mean": el.map(x => x.measure).reduce((a, b) => { return a + b; }) / el.length });
                });
            });

            data = data.flat()

            return data;

        },
        groupBy(list, keyGetter) {
            const map = new Map();
            Array.prototype.forEach.call(list, item => {
                const key = keyGetter(item);
                const collection = map.get(key);
                if (!collection) {
                    map.set(key, [item]);
                } else {
                    collection.push(item);
                }
            });
            return map;
        }
    }
})