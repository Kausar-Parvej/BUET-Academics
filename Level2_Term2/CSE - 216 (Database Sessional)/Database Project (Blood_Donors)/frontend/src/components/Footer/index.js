import React from "react";
import "../../../node_modules/bootstrap/dist/css/bootstrap.min.css";
import "./style.css";

export default function PageFooter({ color }) {
  return (
    <>
      <footer class="footer-distributed">
        <div class="footer">
          <p>
            <h5>CSE 216 Database Project &copy; 2023</h5>
          </p>
          <br></br>

          <div class="container-fluid footer-links">
            <div class="row">
              <div class="col-md-2"></div>
              {/* <div class="col-md-2"></div> */}
              <div class="col-md-4">
                <p class="footer-links">S. M. Kausar Parvej</p>
                <p class="footer-links">2005076</p>
                <p class="footer-links"><em><a href="mailto:kausarparvej3@gmail.com">kausarparvej3@gmail.com</a></em></p>
              </div>
              <div class="col-md-4">
                <p class="footer-links">Iffat Hossain</p>
                <p class="footer-links">2005087</p>
                <p class="footer-links"><em><a href="mailto:1805040@ugrad.cse.buet.ac.bd">iffat@gmail.com</a></em></p>              
                </div>
              {/* <div class="col-md-2"></div> */}
              <div class="col-md-2"></div>
            </div>
          </div>
        </div>
      </footer>
    </>
  );
}
