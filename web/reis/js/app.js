/*

Tupã Cloud. 2021.

*/


const API_ENDPOINT = "https://mushroom.api.tupacloud.com/";
var ctx = document.getElementById('chart').getContext('2d');
var chart = null;
var chartData = null;

function start() {
    getValues();
}

function updateScale(scaleby) {
    if (scaleby == "day") {
        var newData = scale_by_day(chartData).flat(); 

        var data = newData.map((el) => el.mean);
        var labels = newData.map((el) => el.label);

        chart.data.labels = labels;
        chart.data.datasets[0].data = data;
        chart.update();

        console.log(data, labels);
    }
    else if (scaleby == "month") {
        var newData = scale_by_month(chartData).flat(); 

        var data = newData.map((el) => el.mean);
        var labels = newData.map((el) => el.label);

        chart.data.labels = labels;
        chart.data.datasets[0].data = data;
        chart.update();

        console.log(data, labels);
    }
    else if (scaleby == "year") {
        var newData = scale_by_year(chartData); 

        var data = newData.map((el) => el.mean);
        var labels = newData.map((el) => el.label);

        chart.data.labels = labels;
        chart.data.datasets[0].data = data;
        chart.update();

        console.log(data, labels);
    }
    else if (scaleby == "none") {
        var newData = chartData; 
            
        var data = newData.filter(el => el.measure > 0).map((el) => el.measure);
        var labels = newData.filter(el => el.measure > 0).map((el) => el.date);

        chart.data.labels = labels;
        chart.data.datasets[0].data = data;
        chart.update();
        
        console.log(data, labels);
    }
}

function changeChartTo(type) {
    var dados = chart.data;
    var opt = chart.opt;

    chart.destroy();

    chart = new Chart(ctx, {
        type: type,
        data: dados,
        options: opt
    });
}

function getValues() {
    var input = '&INPUT={wBeeName: "caixa preta", lastMeasure: [{date:"2020-12-01T13:03:24.472Z"}], cid: "cid_00", dbs: "besouro", col: "clients"}'
    var flow = 'FLOW=%7B%22flush%22%3A%22S0ydU20FEAO%2Bsb1oCBItR3CP7tw6umayvMPpkBwJFJN5VNh9ncekEJWFYJ8nrfrc0n8JgX3E%2B36L8LFueZO1KA%3D%3D%22%2C%22i' +
                'ntegrity%22%3A%2250aee3d861fc78e96ab7587c9dd16fbf%22%2C%22security_token%22%3A%222b9093f71f43ffdf6eaf31445253cb1d98af1241fdee2e611' +
                '3b3948510e847aba4e3e6061304f3213e402a0fd7a6d07495dfcdedfe02290d7bdbfb8f424a206aaefedfd1b9f858133e3c96ce4864080acc288738cf4404aed0c' +
                'cccee8ab6c5e9e3f1487c613c6c840d43776ee0e1e703ebbb377999f98c9f0f62abe3f5d45e623a8538b606df9a8cef4377345df5637669565d1aed4f31de629a3' +
                '9fa4b7593e30e3cfbfae348f6d3c123261ebc0a110943665a9636c671eb81152b62e038499f30eb63f6301401f4471902045caf046b907219d9f76e4283e11f84c' +
                '88781d66b3b0fe9df3fc506a5034eb02dd77cb67b56d8c83596a82edca9677eca8a0e9b6a%22%7D';            
    var flush = flow + input;

    $.ajax({
        type: "POST",
        crossdomain: true,
        cache: false,
        beforeSend: function () {
            $('#loader').show();
        },
        url: API_ENDPOINT,
        data: { URL: flush },
        complete: function () {
            $('#loader').hide();
        },
        success: function (res) {

            var ms = JSON.parse(res).sort((a, b) => new Date(a.date) - new Date(b.date));
            
            var data = ms.filter(el => el.measure > 0).map((el) => el.measure);
            var labels = ms.filter(el => el.measure > 0).map((el) => el.date);

            console.log(data, labels);

            createChart(data, labels);

            chartData = ms;
            //scale(ms);

        }
    });
}

function scale_by_day(dt) {

    var dt = dt.filter(el => el.measure > 0); // remove 0s. retirar essa linha no futuro
    var groupByYear = groupBy(dt, x => new Date(x.date).getFullYear());
    var groups = [];
    var data = [];

    groupByYear.forEach((el) => {
        groups.push(groupBy(el, x => 2**(new Date(x.date).getDate()) * 3**(new Date(x.date).getMonth() + 1)));
    });

    groups.forEach((year) => {
        data.push([]);
        year.forEach((el) => {
            var month = new Date(el[0].date).getMonth() + 1;
            var label = new Date(el[0].date).getDate() + '/' + month + '/' + new Date(el[0].date).getFullYear();
            data[data.length-1].push( {"label" : label , "mean" : el.map(x => x.measure).reduce((a,b) => { return a + b; }) / el.length });
        });
    });

    return data;

}

function scale_by_month(dt) {

    var dt = dt.filter(el => el.measure > 0); // remove 0s. retirar essa linha no futuro
    var groupByYear = groupBy(dt, x => new Date(x.date).getFullYear());
    var groups = [];
    var data = [];

    groupByYear.forEach((el) => {
        groups.push(groupBy(el, x => new Date(x.date).getMonth()));
    });

    groups.forEach((year) => {
        data.push([]);
        year.forEach((el) => {
            var label = new Date(el[0].date).getMonth() + 1 + '/' + new Date(el[0].date).getFullYear();
            data[data.length-1].push( {"label" : label , "mean" : el.map(x => x.measure).reduce((a,b) => { return a + b; }) / el.length });
        });
    });

    return data;

}

function scale_by_year(dt) {

    var dt = dt.filter(el => el.measure > 0); // remove 0s. retirar essa linha no futuro
    var groupByYear = groupBy(dt, x => new Date(x.date).getFullYear());
    var data = [];

    groupByYear.forEach((el) => {

        var label = new Date(el[0].date).getFullYear();
        data.push( {"label" : label , "mean" : el.map(x => x.measure).reduce((a,b) => { return a + b; }) / el.length });


    });

    return data;

}



function createChart(dt, lb) {

    var dados = {
        labels: lb,
        datasets: [{
            label: 'Nível da água',
            data: dt,
            backgroundColor: 'rgba(54, 162, 235, 0.8)',
            borderColor: 'rgba(0, 0, 0, 1)',
            borderWidth: 1
        }]
    };

    var opt = {
        responsive: false,
        maintainAspectRatio: false,
        scales: {
            yAxes: [{
                ticks: {
                    beginAtZero: true
                }
            }]
        }
    };

    chart = new Chart(ctx, {
        type: 'bar',
        data: dados,
        options: opt
    });


}

/**
 * @description
 * Takes an Array<V>, and a grouping function,
 * and returns a Map of the array grouped by the grouping function.
 *
 * @param list An array of type V.
 * @param keyGetter A Function that takes the the Array type V as an input, and returns a value of type K.
 *                  K is generally intended to be a property key of V.
 *
 * @returns Map of the array grouped by the grouping function.
 */
//export function groupBy<K, V>(list: Array<V>, keyGetter: (input: V) => K): Map<K, Array<V>> {
//    const map = new Map<K, Array<V>>();
function groupBy(list, keyGetter) {
    const map = new Map();
    list.forEach((item) => {
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



