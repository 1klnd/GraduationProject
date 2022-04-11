$.getJSON('https://localhost:8899/api/SettingValues?from=2022-02-11T06%3A33%3A13.463Z&to=2022-04-11T06%3A33%3A13.463Z',
    function (rawsvdata) {
        $.getJSON('https://localhost:8899/api/MeasuredValues?from=2022-03-14T15%3A19%3A00.435251&to=2022-03-14T15%3A50%3A44.409848',
            function (rawmvdata) {
                var options = {
                    chart: {
                        renderTo: 'container-hum'
                    },
                    title: {
                        text: "湿度"
                    },
                    xAxis: {
                        type: 'datetime',
                        min: Date.parse('2022-03-14T15:19:00.435251'),
                        max: Date.parse('2022-03-14T15:50:44.409848')
                    },
                    series: [{ type: "line", name: "SettingValue" },
                    { type: "spline", name: "MeasuredValue" }]
                };

                var svdata = [{}]
                rawsvdata.forEach(e => {
                    svdata.push([Date.parse(e.time), e.temperature])
                });
                options.series[0].data = svdata;

                var mvdata = [{}]
                rawmvdata.forEach(e => {
                    mvdata.push([Date.parse(e.time), e.humidity])
                });
                options.series[1].data = mvdata;

                Highcharts.setOptions({
                    global: {
                        timezoneOffset: -8 * 60
                    }
                });
                Highcharts.chart('container-hum', options);
            })
    })
