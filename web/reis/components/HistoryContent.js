app.component('history-content', {
    data() {
        return {
            opt: null,
            dados: null,
            chart: null,
            ctx: null
        }
    },
    props: {
        data: {
            type: Array,
            required: true
        },
        labels: {
            type: Array,
            required: true
        },
        id: {
            type: String,
            required: true
        }
    },
    template:
    /*html*/
    `
    <div class="history-content">
        <div class="history-options">
            <h4>Tipo de gráfico</h4>
            <button type="button" class="display btn btn-dark" v-on:click="changeType('bar')">Barras</button>
            <button type="button" class="display btn btn-dark" v-on:click="changeType('line')">Linhas</button>
            <button type="button" class="display btn btn-dark" v-on:click="changeType('radar')">Radar</button><br/>
        </div>
        <div class="history-chart">
            <canvas :id="id" width="600" height="600" class="chart"></canvas>
        </div>
    </div>
    `,
    mounted: function() {
        this.makeChart(this.data, this.labels);
    },
    methods: {
        changeType(type) {

            this.chart.destroy();

            this.chart = new Chart(this.ctx, {
                type: type,
                data: this.dados,
                options: this.opt
            });
        },
        makeChart(dt, lb) {
            this.ctx = document.getElementById(this.id).getContext('2d');

            this.dados = {
                labels: lb,
                datasets: [{
                    label: 'Nível da água',
                    data: dt,
                    backgroundColor: 'rgba(176,196,222, 1)',
                    borderColor: 'rgba(176,196,222, 1)',
                    borderWidth: 1
                }]
            };

            this.opt = {
                legend: {
                    labels: {
                        fontColor: "white",
                        fontSize: 18
                    }
                },
                responsive: false,
                maintainAspectRatio: false,
                scales: {
                    yAxes: [{
                        ticks: {
                            fontColor: "white",
                            fontSize: 18,
                            stepSize: 1,
                            beginAtZero: true
                        }
                    }],
                    xAxes: [{
                        ticks: {
                            fontColor: "white",
                            fontSize: 14,
                            stepSize: 1,
                            beginAtZero: true
                        }
                    }]
                }
            };

            this.chart = new Chart(this.ctx, {
                type: 'bar',
                data: this.dados,
                options: this.opt
            });

            $('#chart').show();
        },
    }

})