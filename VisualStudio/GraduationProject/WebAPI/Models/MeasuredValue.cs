namespace WebAPI.Models
{
    public record class MeasuredValue
    {
        public int ID { get; set; }
        public double Temperature { get; set; }
        public double Humidity { get; set; }
        public DateTime Time { get; set; }
    }
}
