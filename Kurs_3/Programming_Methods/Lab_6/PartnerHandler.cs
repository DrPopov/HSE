using System;
using System.Collections.Generic;
using System.Text;

namespace laba6.Handlers
{
    public class PartnerHandler: Handler
    {
        public override void Handle(Order order) {
            if (order.ClientNumber.StartsWith("PT")) {
                Console.WriteLine("Заказчик - наш партнер. Выполняем по ускоренной процедуре!");
                order.Number = "PT-" + Guid.NewGuid().ToString();
            } else {
                if (Successor != null)
                    Successor.Handle(order);
            }
        }
    }
}
