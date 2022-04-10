#nullable disable
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using WebAPI.Data;
using WebAPI.Models;

namespace WebAPI.Controllers
{
    [Route("api")]
    [ApiController]
    public class MeasuredValuesController : ControllerBase
    {
        private readonly WebAPIContext _context;

        public MeasuredValuesController(WebAPIContext context)
        {
            _context = context;
        }

        // GET: api/MeasuredValues
        [HttpGet("MeasuredValues")]
        public async Task<ActionResult<IEnumerable<MeasuredValue>>> GetMeasuredValues(string from, string to)
        {
            // the same as it in SettingValuesController
            DateTime fromdt, todt;

            if (DateTime.TryParse(from, out fromdt) && DateTime.TryParse(to, out todt))
            {
                // no need to get the last measured value, see also in SettingValuesController
                return await _context.MeasuredValue.Where(v => v.Time > fromdt && v.Time < todt).ToListAsync();
            }
            else
            {
                return BadRequest();
            }
        }

        // POST: api/MeasuredValues
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPost("MeasuredValue")]
        public async Task<ActionResult<MeasuredValue>> PostMeasuredValue(double temperature, double humidity)
        {
            var measuredvalue = new MeasuredValue();
            measuredvalue.Temperature = temperature;
            measuredvalue.Humidity = humidity;
            measuredvalue.Time = DateTime.Now;

            _context.MeasuredValue.Add(measuredvalue);
            await _context.SaveChangesAsync();

            return Ok();
        }

        // OPTIONS is needed to pass the preflight from browser
        [HttpOptions("MeasuredValue")]
        public async Task<ActionResult<SettingValue>> OptionsMeasuredValue()

        {
            return Ok();
        }
    }
}
