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
    public class SettingValuesController : ControllerBase
    {
        private readonly WebAPIContext _context;

        public SettingValuesController(WebAPIContext context)
        {
            _context = context;
        }

        // GET: api/SettingValue
        [HttpGet("SettingValue")]
        public async Task<ActionResult> GetSettingValue()
        {
            var settingvalue = await _context.SettingValue.OrderBy(v => v.ID).LastAsync();

            if(settingvalue != null)
            {
                return Ok( new {
                    temperature = settingvalue.Temperature,
                    humidity    = settingvalue.Humidity });
            }
            else
            {
                return NotFound();
            }
        }


        // GET: api/SettingValues
        [HttpGet("SettingValues")]
        public async Task<ActionResult<IEnumerable<SettingValue>>> GetSettingValues(string from, string to)
        {
            // parameter from/to use the ISO 8601 format to refer to a time point, for example
            // ?from=2018-08-18T07:22:16.0000000Z&to=2028-08-18T07:22:16.0000000Z
            // string in other styles may also succeed

            DateTime fromdt, todt;

            if(DateTime.TryParse(from, out fromdt) && DateTime.TryParse(to, out todt))
            {
                var settingvalues = await _context.SettingValue.Where(v => v.Time > fromdt && v.Time < todt).ToListAsync();
                if( settingvalues.First().ID != 1)
                { 
                    // Insert the setting value at the beginning
                    settingvalues.Insert(0, _context.SettingValue.Find( settingvalues.First().ID - 1 )); 
                }
                return Ok( settingvalues );
            }

            else
            {
                return BadRequest();
            }
        }

  
        // POST: api/SettingValue
        [HttpPost("SettingValue")]
        public async Task<ActionResult<SettingValue>> PostSettingValue(double temperature, double humidity)
        {
            var settingvalue = new SettingValue();
            settingvalue.Temperature = temperature;
            settingvalue.Humidity = humidity;
            settingvalue.Time = DateTime.Now;

            _context.SettingValue.Add(settingvalue);
            await _context.SaveChangesAsync();

            return Ok();
        }

        // OPTIONS is needed to pass the preflight from browser
        [HttpOptions("SettingValue")]
        public async Task<ActionResult<SettingValue>> OptionsSettingValue()
        {
            return Ok();
        }

    }
}
